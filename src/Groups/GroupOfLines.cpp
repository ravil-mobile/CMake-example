/*
 * GroupOfLines.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: ravil
 */

#include <iostream>
#include "GroupOfLines.h"
#include "../Nodes/NodeList.h"

const unsigned int GroupOfLines::NUMBER_NODES_PER_ELEMENT = 2;

GroupOfLines::GroupOfLines() : Group() {
	// TODO Auto-generated constructor stub

}


GroupOfLines::GroupOfLines( unsigned int Index,
							std::string Name,
							std::shared_ptr<const NodeList> Nodes )
											: Group( Index, Name, Nodes ) {

}


GroupOfLines::~GroupOfLines() {
	// TODO Auto-generated destructor stub
}


void GroupOfLines::insertElement(std::vector<unsigned int> Bundle) {
	unsigned int DISPLACEMENT = 1;
	m_ListOfElemets.push_back \
		( std::shared_ptr<const LinearElementType>
			( new LinearElementType( Bundle[0],
						m_Nodes->getNode( Bundle[5] - DISPLACEMENT ),
						m_Nodes->getNode( Bundle[6] - DISPLACEMENT ))));
}


void GroupOfLines::updateLinearSystem() {
	if ( m_Condition.get() != 0 )
		m_Condition->updateLinearSystem( m_ListOfElemets );
}


unsigned int GroupOfLines::getNumberOfElements() {
	return m_ListOfElemets.size();
}


unsigned int GroupOfLines::getNumberOfEntriesInVtkTable() {
	unsigned int NumberOfEntriesInLine( NUMBER_NODES_PER_ELEMENT );
	return ( (++NumberOfEntriesInLine) * m_ListOfElemets.size() );
}


void GroupOfLines::printElementsAccordingToVtkFormat
								( std::streambuf* OutputBuffer ) {
	for ( auto Iterator = m_ListOfElemets.begin();
		  Iterator != m_ListOfElemets.end();
		  ++Iterator ) {

		print( std::to_string( NUMBER_NODES_PER_ELEMENT )
			 + " "
			 + std::to_string( Iterator->get()->getFirstNode()->getGlobalIndex())
			 + " "
			 + std::to_string( Iterator->get()->getSecondNode()->getGlobalIndex()),
			   OutputBuffer );
	}
}


void GroupOfLines::printElementsTypeAccordingToVtkFormat
								( std::streambuf* OutputBuffer ) {
	for ( auto Iterator = m_ListOfElemets.begin();
			  Iterator != m_ListOfElemets.end();
			  ++Iterator ) {

		print( std::to_string(Iterator->get()->getElementType()),
			   OutputBuffer );

		}
}


void GroupOfLines::getInfo() {

	std::cout << "*********************************" << std::endl;
	std::cout << "Type: " << "Group Of Lines" << std::endl;
	std::cout << "Index: " << m_Index << std::endl;
	std::cout << "Name: " << m_Name << std::endl;
	std::cout << "#Elements: " << m_ListOfElemets.size() << std::endl;
	std::cout << "Update Priority: " << m_Condition->getUpdatePriority() << std::endl;

	if ( isGroupReady() )
		m_Condition.get()->printInformation();
	std::cout << std::endl;
}
