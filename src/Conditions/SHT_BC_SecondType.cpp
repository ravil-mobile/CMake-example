/*
 * SecondBoundaryCondition.cpp
 *
 *  Created on: Mar 30, 2017
 *      Author: ravil
 */

#include "SHT_BC_SecondType.h"

SHT_BC_SecondType::SHT_BC_SecondType() : m_Flux( 0.0 ) {
	// TODO Auto-generated constructor stub

}


SHT_BC_SecondType::~SHT_BC_SecondType() {
	// TODO Auto-generated destructor stub
}


SHT_BC_SecondType::SHT_BC_SecondType(
					double Flux,
					std::shared_ptr<Matrix> GlobalStiffnessMatrix,
					std::shared_ptr<Matrix> MassMatrix,
					std::shared_ptr<Vector> RightHandSide) :
							 AbstractCondition( GlobalStiffnessMatrix,
												MassMatrix,
												RightHandSide ),
												m_Flux( Flux ) {
}


void SHT_BC_SecondType::updateLinearSystem(
		std::vector<std::shared_ptr<const LinearElementType>> Lines ) {

	if ( m_Flux == 0.0 ) {
		std::cout << "Linear group has been updated" << std::endl;
		return; }

	// Precompute the local stiffness matrix for the reference linear element
	Matrix LocalStiffnessMatrix(2,2);
	LocalStiffnessMatrix(0,0) = 1.0 / 3.0;
	LocalStiffnessMatrix(0,1) = 1.0 / 6.0;
	LocalStiffnessMatrix(1,0) = LocalStiffnessMatrix(0,1);
	LocalStiffnessMatrix(1,1) = LocalStiffnessMatrix(0,0);


	double Length = 0.0;
	double DeltaX = 0.0;
	double DeltaY = 0.0;
	for ( auto Iterator = Lines.begin();
		Iterator != Lines.end();
		++Iterator ) {

			// Precompute the length of the current element
		DeltaX = (*Iterator)->getSecondNode()->getCoordianteX()
			   - (*Iterator)->getFirstNode()->getCoordianteX();

		DeltaY = (*Iterator)->getSecondNode()->getCoordianteY()
			   - (*Iterator)->getFirstNode()->getCoordianteY();

		Length = sqrt( (DeltaX * DeltaX) + ( DeltaY * DeltaY ) );

			// update the global stiffness matrix and the right hand side
		updateRightHandSide( *Iterator, LocalStiffnessMatrix, Length );
	}

		std::cout << "Linear group has been updated" << std::endl;
}


void SHT_BC_SecondType::updateRightHandSide( std::shared_ptr<const LinearElementType> anElement,
											 const Matrix& LocalReferenceStiffnessMatrix,
											 const double Length) {


	const double PrecomputedCoefficient = m_Flux * Length;

		(*m_RightHandSide)( anElement->getFirstNode()->getGlobalIndex() )
			+= PrecomputedCoefficient * LocalReferenceStiffnessMatrix(0,0);

		(*m_RightHandSide)( anElement->getFirstNode()->getGlobalIndex() )
			+= PrecomputedCoefficient * LocalReferenceStiffnessMatrix(0,1);



		(*m_RightHandSide)( anElement->getSecondNode()->getGlobalIndex() )
			+= PrecomputedCoefficient * LocalReferenceStiffnessMatrix(1,0);

		(*m_RightHandSide)( anElement->getSecondNode()->getGlobalIndex() )
			+= PrecomputedCoefficient * LocalReferenceStiffnessMatrix(1,1);

}



// ******************** Process member variable ******************** //

	// ******************** Setter functions ******************** //

void SHT_BC_SecondType::setFlux ( double FLux ) {
	m_Flux = FLux;
}


	// ******************** Getter function ********************

double SHT_BC_SecondType::getFlux() {
	return m_Flux;
}


Priority SHT_BC_SecondType::getUpdatePriority() {
	return THIRD;
}

	// ******************** Print function ********************

void SHT_BC_SecondType::printInformation() {
	std::cout << "Flux: " << m_Flux << std::endl;
}

