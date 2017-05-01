/*
 * ThirdBoudaryCondition.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: ravil
 */

#include <cmath>

#include "SHT_BC_ThirdType.h"

#include "AbstractCondition.h"
#include "../Elements/AbstractElementType.h"
#include "../Elements/LinearElementType.h"
#include "../Elements/TriangularElementType.h"


SHT_BC_ThirdType::SHT_BC_ThirdType() : AbstractCondition( 0, 0, 0 ),
				m_EnvironmentTemperature( 0.0 ),
				m_HeatTransfer( 0.0 ),
				m_ConductivityCoefficient( 0.0 ),
				m_ScaleCoefficient ( 0.0 ) {
	// TODO Auto-generated constructor stub

}

SHT_BC_ThirdType::SHT_BC_ThirdType( double EnvironmentTemperature,
							double HeatTransfer,
							double ConductivityCoefficient,
							std::shared_ptr<Matrix> GlobalStiffnessMatrix,
							std::shared_ptr<Matrix> MassMatrix,
							std::shared_ptr<Vector> RightHandSide)

					: AbstractCondition( GlobalStiffnessMatrix,
										 MassMatrix,
										 RightHandSide ),
					  m_EnvironmentTemperature( EnvironmentTemperature ),
					  m_HeatTransfer( HeatTransfer ),
					  m_ConductivityCoefficient( ConductivityCoefficient ),
					  m_ScaleCoefficient ( 0.0 ) {
}


SHT_BC_ThirdType::~SHT_BC_ThirdType() {
	// TODO Auto-generated destructor stub
}


void SHT_BC_ThirdType::updateLinearSystem(
		std::vector<std::shared_ptr<const LinearElementType>> Lines ) {


	// Precompute the local stiffness matrix for the reference linear element
	Matrix LocalStiffnessMatrix(2,2);
	LocalStiffnessMatrix(0,0) = 1.0 / 3.0;
	LocalStiffnessMatrix(0,1) = 1.0 / 6.0;
	LocalStiffnessMatrix(1,0) = LocalStiffnessMatrix(0,1);
	LocalStiffnessMatrix(1,1) = LocalStiffnessMatrix(0,0);


	// Precompute the ScaleCoefficient that is equal to:
	//	Heat_Transfer_Coefficient / Conductivity_Coefficient
	computeScaleCoefficient();


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
		updateGlobalStiffnessMatrix( *Iterator, LocalStiffnessMatrix, Length );
		updateRightHandSide( *Iterator, LocalStiffnessMatrix, Length );
	}

	std::cout << "Linear group has been updated" << std::endl;

}


void SHT_BC_ThirdType::updateGlobalStiffnessMatrix
					( std::shared_ptr<const LinearElementType> anElement,
					  const Matrix& LocalReferenceStiffnessMatrix,
					  const double Length ) {

	const double PrecomputedCoefficient = m_ScaleCoefficient
										* Length;


	(*m_GlobalStiffnessMatrix)( anElement->getFirstNode()->getGlobalIndex(),
								anElement->getFirstNode()->getGlobalIndex() )
		-= PrecomputedCoefficient * LocalReferenceStiffnessMatrix(0,0);

	(*m_GlobalStiffnessMatrix)( anElement->getFirstNode()->getGlobalIndex(),
								anElement->getSecondNode()->getGlobalIndex() )
		-= PrecomputedCoefficient * LocalReferenceStiffnessMatrix(0,1);




	(*m_GlobalStiffnessMatrix)( anElement->getSecondNode()->getGlobalIndex(),
								anElement->getFirstNode()->getGlobalIndex() )
		-= PrecomputedCoefficient * LocalReferenceStiffnessMatrix(1,0);

	(*m_GlobalStiffnessMatrix)( anElement->getSecondNode()->getGlobalIndex(),
								anElement->getSecondNode()->getGlobalIndex() )
		-= PrecomputedCoefficient * LocalReferenceStiffnessMatrix(1,1);

}

void SHT_BC_ThirdType::updateRightHandSide
					( std::shared_ptr<const LinearElementType> anElement,
					  const Matrix& LocalReferenceStiffnessMatrix,
					  const double Length ) {

	const double PrecomputedCoefficient = m_ScaleCoefficient
										* m_EnvironmentTemperature
										* Length;

	(*m_RightHandSide)( anElement->getFirstNode()->getGlobalIndex() )
		-= PrecomputedCoefficient * LocalReferenceStiffnessMatrix(0,0);

	(*m_RightHandSide)( anElement->getFirstNode()->getGlobalIndex() )
		-= PrecomputedCoefficient * LocalReferenceStiffnessMatrix(0,1);



	(*m_RightHandSide)( anElement->getSecondNode()->getGlobalIndex() )
		-= PrecomputedCoefficient * LocalReferenceStiffnessMatrix(1,0);

	(*m_RightHandSide)( anElement->getSecondNode()->getGlobalIndex() )
		-= PrecomputedCoefficient * LocalReferenceStiffnessMatrix(1,1);

}


void SHT_BC_ThirdType::computeScaleCoefficient() {

	try {
		if ( m_ConductivityCoefficient != 0.0 ) {
			m_ScaleCoefficient = m_HeatTransfer / m_ConductivityCoefficient;
		}
		else {
			int Error(1);
			throw Error;
		}

	}
	catch( int DevisionByZero ) {
		// Write the warning message to inform the user
		std::cout << "Non-physical material properties"
				  << std::endl
				  << "The Conductivity Coefficient is equal to zero"
				  << std::endl;

		throw DevisionByZero;
	}
}


// ******************** Process member variable ******************** //

	// ******************** Setter functions ******************** //

void SHT_BC_ThirdType::setEnvironmentTemperature
							( double EnvironmentTemperature ) {
	m_EnvironmentTemperature = EnvironmentTemperature;
}


void SHT_BC_ThirdType::setHeatTransfer
							( double HeatTransfer ) {
	m_HeatTransfer = HeatTransfer;
}


void SHT_BC_ThirdType::setConductivityCoefficient
							( double ConductivityCoefficient ) {
	m_ConductivityCoefficient = ConductivityCoefficient;
}


	// ******************** Getter function ********************

double SHT_BC_ThirdType::getEnvironmentTemperature() {
	return m_EnvironmentTemperature;
}


double SHT_BC_ThirdType::getHeatTransfer() {
	return m_HeatTransfer;
}


double SHT_BC_ThirdType::getConductivityCoefficient() {
	return m_ConductivityCoefficient;
}


Priority SHT_BC_ThirdType::getUpdatePriority() {
	return SECOND;
}


	// ******************** Print function ********************
void SHT_BC_ThirdType::printInformation() {

	std::cout << "EnvironmentTemperature: " << m_EnvironmentTemperature << std::endl;
	std::cout << "HeatTransfer: " << m_HeatTransfer << std::endl;
	std::cout << "ConductivityCoefficient: " << m_ConductivityCoefficient << std::endl;
}
