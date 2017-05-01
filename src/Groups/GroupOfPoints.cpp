/*
 * GroupOfDots.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: ravil
 */


#include <iostream>
#include "GroupOfPoints.h"
#include "../Nodes/NodeList.h"


const unsigned int GroupOfPoints::NUMBER_NODES_PER_ELEMENT = 1;

GroupOfPoints::GroupOfPoints() : Group() {
	// TODO Auto-generated constructor stub

}

GroupOfPoints::GroupOfPoints(unsigned int Index,
						 std::string Name,
						 std::shared_ptr<const NodeList> Nodes )
										: Group( Index, Name, Nodes ) {
}

GroupOfPoints::~GroupOfPoints() {
	// TODO Auto-generated destructor stub
}

void GroupOfPoints::insertElement(std::vector<unsigned int> Bundle) {
	unsigned int DISPLACEMENT = 1;
	m_ListOfElemets.push_back \
			( std::shared_ptr<PointElementType const > \
				( new PointElementType( Bundle[0],
								m_Nodes->getNode( Bundle[5] - DISPLACEMENT ))));
}

void GroupOfPoints::updateLinearSystem() {
	if ( isGroupReady() )
		m_Condition->updateLinearSystem( m_ListOfElemets );
}


unsigned int GroupOfPoints::getNumberOfElements() {
	return m_ListOfElemets.size();
}


unsigned int GroupOfPoints::getNumberOfEntriesInVtkTable() {
	unsigned int NumberOfEntriesInLine( NUMBER_NODES_PER_ELEMENT );
	return ( (++NumberOfEntriesInLine) * m_ListOfElemets.size() );
}


void GroupOfPoints::printElementsAccordingToVtkFormat
								( std::streambuf* OutputBuffer ) {
	for ( auto Iterator = m_ListOfElemets.begin();
		  Iterator != m_ListOfElemets.end();
		  ++Iterator ) {

		std::cout << NUMBER_NODES_PER_ELEMENT
				  << " "
				  << Iterator->get()->getFirstNode()->getGlobalIndex()
				  << std::endl;
	}
}


void GroupOfPoints::printElementsTypeAccordingToVtkFormat
								( std::streambuf* OutputBuffer ) {
	for ( auto Iterator = m_ListOfElemets.begin();
			  Iterator != m_ListOfElemets.end();
			  ++Iterator ) {

		print( std::to_string( NUMBER_NODES_PER_ELEMENT )
			 + " "
			 + std::to_string( Iterator->get()->getFirstNode()->getGlobalIndex()),
			   OutputBuffer );

		}
}


void GroupOfPoints::getInfo() {
	std::cout << "*********************************" << std::endl;
	std::cout << "Type: " << "Group Of Dots" << std::endl;
	std::cout << "Index: " << m_Index << std::endl;
	std::cout << "Name: " << m_Name << std::endl;
	std::cout << "#Elements: " << "--undefined--" << std::endl;
	std::cout << "Update Priority: " << m_Condition->getUpdatePriority() << std::endl;


	if ( isGroupReady() )
		m_Condition.get()->printInformation();
	std::cout << std::endl;
}
