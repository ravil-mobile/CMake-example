/*
 * FirstBoundaryCondition.cpp
 *
 *  Created on: Mar 30, 2017
 *      Author: ravil
 */

#include "SHT_BC_FirstType.h"


SHT_BC_FirstType::SHT_BC_FirstType() : AbstractCondition( 0, 0, 0 ),
									   m_WallTemperature( 0.0 )  {
	// TODO Auto-generated constructor stub

}


SHT_BC_FirstType::~SHT_BC_FirstType() {
	// TODO Auto-generated destructor stub
}


SHT_BC_FirstType::SHT_BC_FirstType( double WallTemperature,
		std::shared_ptr<Matrix> GlobalStiffnessMatrix,
		std::shared_ptr<Matrix> MassMatrix,
		std::shared_ptr<Vector> RightHandSide)
										: AbstractCondition( GlobalStiffnessMatrix,
															 MassMatrix,
															 RightHandSide ),
										  m_WallTemperature( WallTemperature ) {
}


void SHT_BC_FirstType::updateLinearSystem(
		std::vector<std::shared_ptr<const PointElementType>> Points ) {

	std::cout << "The implementation of the first type boundary condition\n"
			  << "for the point elements is not read"
			  << std::endl;
}



void SHT_BC_FirstType::updateLinearSystem
		( std::vector<std::shared_ptr<const LinearElementType>> Lines ) {

	for ( auto Iterator = Lines.begin();
		  Iterator != Lines.end();
		  ++Iterator) {

		updateRightHandSide( *Iterator );
		updateGlobalStiffnessMatrix( *Iterator );


	}


	std::cout << "Linear group has been updated" << std::endl;

}

void SHT_BC_FirstType::updateGlobalStiffnessMatrix(
		std::shared_ptr<const LinearElementType> anElement ) {

	unsigned int NodeGlobalIndex = 0;

	// Update the row associated with first node of a linear element
	NodeGlobalIndex = anElement->getFirstNode()->getGlobalIndex();
	(*m_GlobalStiffnessMatrix).setStringToZero( NodeGlobalIndex );

	(*m_GlobalStiffnessMatrix)(NodeGlobalIndex, NodeGlobalIndex)
			= (*m_RightHandSide).getVectorReferenceCounter(NodeGlobalIndex);


	// Update the row associated with second node of a linear element
	NodeGlobalIndex = anElement->getSecondNode()->getGlobalIndex();
	(*m_GlobalStiffnessMatrix).setStringToZero( NodeGlobalIndex );

	(*m_GlobalStiffnessMatrix)(NodeGlobalIndex,NodeGlobalIndex)
			= (*m_RightHandSide).getVectorReferenceCounter(NodeGlobalIndex);

}

void SHT_BC_FirstType::updateRightHandSide(
		std::shared_ptr<const LinearElementType> anElement ) {

	unsigned int NodeGlobalIndex = 0;

	// Update the row associated with first node of a linear element
	NodeGlobalIndex = anElement->getFirstNode()->getGlobalIndex();
	(*m_RightHandSide)(NodeGlobalIndex) += m_WallTemperature;
	(*m_RightHandSide).incrementVectorReferenceCounter( NodeGlobalIndex );

	// Update the row associated with second node of a linear element
	NodeGlobalIndex = anElement->getSecondNode()->getGlobalIndex();
	(*m_RightHandSide)(NodeGlobalIndex) += m_WallTemperature;
	(*m_RightHandSide).incrementVectorReferenceCounter( NodeGlobalIndex );

}



// ******************** Process member variable ******************** //

	// ******************** Setter functions ******************** //

void SHT_BC_FirstType::setWallTemperature( double WallTemperature ) {
	m_WallTemperature = WallTemperature;
}


	// ******************** Getter function ********************

double SHT_BC_FirstType::getWallTemperature() {
	return m_WallTemperature;
}

Priority SHT_BC_FirstType::getUpdatePriority() {
	return FOURTH;
}


	// ******************** Print function ********************

void SHT_BC_FirstType::printInformation() {
	std::cout << "WallTemperature: " << m_WallTemperature << std::endl;
}


