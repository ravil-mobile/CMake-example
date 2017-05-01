/*
 * GeneralCondition.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: ravil
 */

#include "SHT_General.h"

#include "AbstractCondition.h"

#include "../Elements/AbstractElementType.h"
#include "../Elements/LinearElementType.h"
#include "../Elements/TriangularElementType.h"

SHT_General::SHT_General() : AbstractCondition( 0, 0, 0 ),
								 m_Temperature( 0.0 ) {
	// TODO Auto-generated constructor stub

}


SHT_General::SHT_General(double Temperature,
		std::shared_ptr<Matrix> GlobalStiffnessMatrix,
		std::shared_ptr<Matrix> MassMatrix,
		std::shared_ptr<Vector> RightHandSide )
								: AbstractCondition( GlobalStiffnessMatrix,
													 MassMatrix,
													 RightHandSide ),
													 m_Temperature( Temperature ) {
}



SHT_General::~SHT_General() {
	// TODO Auto-generated destructor stub
}


void SHT_General::updateLinearSystem(
		std::vector<std::shared_ptr<const TriangularElementType>> Triangles) {


	// Update Global Stiffness Matrix
	for ( auto Iterator = Triangles.begin();
		  Iterator != Triangles.end();
		  ++Iterator ) {
		updateGlobalStiffnessMatrix( *Iterator );
	}

	std::cout << "Trianguar group has been updated" << std::endl;
}

void SHT_General::updateGlobalStiffnessMatrix(
		std::shared_ptr<const TriangularElementType> anElement ) {

	Matrix LocalStffinessMatrix(3,3);

	// Compute the Local Stiffness Matrix for an element
	LocalStffinessMatrix = computeLocalStiffnessMatrix( anElement );


	// Map the first row of the Local Stiffness Matrix to the Global one
		// Notation: (*aMatrix)(i,j) = aMatrix[i,j]
	(*m_GlobalStiffnessMatrix)( anElement->getFirstNode()->getGlobalIndex(),
								anElement->getFirstNode()->getGlobalIndex())
		+= LocalStffinessMatrix( 0, 0 );

	(*m_GlobalStiffnessMatrix)( anElement->getFirstNode()->getGlobalIndex(),
								anElement->getSecondNode()->getGlobalIndex())
		+= LocalStffinessMatrix( 0, 1 );

	(*m_GlobalStiffnessMatrix)( anElement->getFirstNode()->getGlobalIndex(),
								anElement->getThirdNode()->getGlobalIndex())
		+= LocalStffinessMatrix( 0, 2 );


	// Map the second row of the Local Stiffness Matrix to the Global one
	(*m_GlobalStiffnessMatrix)( anElement->getSecondNode()->getGlobalIndex(),
								anElement->getFirstNode()->getGlobalIndex())
		+= LocalStffinessMatrix( 1, 0 );

	(*m_GlobalStiffnessMatrix)( anElement->getSecondNode()->getGlobalIndex(),
								anElement->getSecondNode()->getGlobalIndex())
		+= LocalStffinessMatrix( 1, 1 );

	(*m_GlobalStiffnessMatrix)( anElement->getSecondNode()->getGlobalIndex(),
								anElement->getThirdNode()->getGlobalIndex())
		+= LocalStffinessMatrix( 1, 2 );


	// Map the third row of the Local Stiffness Matrix to the Global one
	(*m_GlobalStiffnessMatrix)( anElement->getThirdNode()->getGlobalIndex(),
								anElement->getFirstNode()->getGlobalIndex())
		+= LocalStffinessMatrix( 2, 0 );

	(*m_GlobalStiffnessMatrix)( anElement->getThirdNode()->getGlobalIndex(),
								anElement->getSecondNode()->getGlobalIndex())
		+= LocalStffinessMatrix( 2, 1 );

	(*m_GlobalStiffnessMatrix)( anElement->getThirdNode()->getGlobalIndex(),
								anElement->getThirdNode()->getGlobalIndex())
		+= LocalStffinessMatrix( 2, 2 );

}

Matrix SHT_General::computeLocalStiffnessMatrix(
		std::shared_ptr<const TriangularElementType> anElement ) {

	/*********************************
	 * Notation of the triangular
	 * 	element structure
	 *
	 * 				 B  Second Node
	 * 				 ^
	 * 			   /   \
	 * 			  A_____C
	 * Y	  First    Third
	 * ^	  Node	    Node
	 * |
	 * |
	 * 0----- >x
	 *
	 ***********************************/

	// Compute the Jacobian matrix
	double ABx = (*anElement).getSecondNode().get()->getCoordianteX()
			   - (*anElement).getFirstNode().get()->getCoordianteX();

	double ABy = (*anElement).getSecondNode().get()->getCoordianteY()
			   - (*anElement).getFirstNode().get()->getCoordianteY();

	double ACx = (*anElement).getThirdNode().get()->getCoordianteX()
			   - (*anElement).getFirstNode().get()->getCoordianteX();

	double ACy = (*anElement).getThirdNode().get()->getCoordianteY()
			   - (*anElement).getFirstNode().get()->getCoordianteY();

	Matrix Jacobian(2,2);

	Jacobian( 0,0 ) = ABx;
	Jacobian( 0,1 ) = ABy;
	Jacobian( 1,0 ) = ACx;
	Jacobian( 1,1 ) = ACy;


	// Compute inverse of the Jacobian matrix and its determinant
	Matrix InverseJacobian(2,2);
	InverseJacobian = Jacobian.getInverseMatrix();

	double Determinant = 0.0;
	Determinant = Jacobian.getMatrixDeterminant();


	// Compute the gradients for basis functions
	Vector FirstBasisGradient
		= InverseJacobian * (*anElement).getFirstBasisReferenceGradient();

	Vector SecondBasisGradient
		= InverseJacobian * (*anElement).getSecondBasisReferenceGradient();

	Vector ThirdBasisGradient
		= InverseJacobian *	(*anElement).getThirdBasisReferenceGradient();


	// Fill in the Local Stiffness Matrix
	Matrix LocalStffinessMatrix(3,3);
	const double ScaleFactor
		= Determinant * (*anElement).getReferenceElementArea();


	// FIRST row of the Local Stiffness Matrix
	LocalStffinessMatrix(0,0) = ScaleFactor
		* vectorInnerProduct( FirstBasisGradient, FirstBasisGradient );

	LocalStffinessMatrix(0,1) = ScaleFactor
		* vectorInnerProduct( FirstBasisGradient, SecondBasisGradient );

	LocalStffinessMatrix(0,2) = ScaleFactor
		* vectorInnerProduct( FirstBasisGradient, ThirdBasisGradient );



	// SECOND row of the Local Stiffness Matrix
	LocalStffinessMatrix(1,0) = LocalStffinessMatrix(0,1);

	LocalStffinessMatrix(1,1) = ScaleFactor
			* vectorInnerProduct( SecondBasisGradient, SecondBasisGradient );

	LocalStffinessMatrix(1,2) = ScaleFactor
			* vectorInnerProduct( SecondBasisGradient, ThirdBasisGradient );



	// THIRD row of the Local Stiffness Matrix
	LocalStffinessMatrix(2,0) = LocalStffinessMatrix(0,2);

	LocalStffinessMatrix(2,1) = LocalStffinessMatrix(1,2);

	LocalStffinessMatrix(2,2) = ScaleFactor
			* vectorInnerProduct( ThirdBasisGradient, ThirdBasisGradient );


	return LocalStffinessMatrix;
}


// ******************** Process member variable ******************** //

	// ******************** Setter functions ******************** //

void SHT_General::setTemperature \
							( double Temperature ) {
	m_Temperature = Temperature;
}


	// ******************** Getter function ********************

double SHT_General::getTemperature() {
	return m_Temperature;
}


	// ******************** Print function ********************

void SHT_General::printInformation() {
	std::cout << "Temperature: " << m_Temperature << std::endl;
}

Priority SHT_General::getUpdatePriority() {
	return FIRST;
}

