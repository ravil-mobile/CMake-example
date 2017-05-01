/*
 * GroupTriangles.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: ravil
 */

#include "GroupOfTriangles.h"
#include "../Elements/TriangularElementType.h"
#include "../Nodes/NodeList.h"

#include <iostream>

const unsigned int GroupOfTriangles::NUMBER_NODES_PER_ELEMENT = 3;

GroupOfTriangles::GroupOfTriangles() : Group() {
	// TODO Auto-generated constructor stub

}


GroupOfTriangles::GroupOfTriangles( unsigned int Index,
									std::string Name,
									std::shared_ptr<const NodeList> Nodes)
									: Group( Index, Name, Nodes ) {

}

GroupOfTriangles::~GroupOfTriangles() {
	// TODO Auto-generated destructor stub
}

void GroupOfTriangles::insertElement(std::vector<unsigned int> Bundle) {
	unsigned int DISPLACEMENT = 1;
	m_ListOfElemets.push_back \
		( std::shared_ptr<TriangularElementType const>
			( new TriangularElementType( Bundle[0],
										 m_Nodes->getNode( Bundle[5] - DISPLACEMENT ),
					 	 	 	 	 	 m_Nodes->getNode( Bundle[6] - DISPLACEMENT ),
										 m_Nodes->getNode( Bundle[7] - DISPLACEMENT))));
}


void GroupOfTriangles::updateLinearSystem() {
	if ( m_Condition.get() != 0 )
		m_Condition->updateLinearSystem( m_ListOfElemets );
}


unsigned int GroupOfTriangles::getNumberOfElements() {
	return m_ListOfElemets.size();
}


unsigned int GroupOfTriangles::getNumberOfEntriesInVtkTable() {
	unsigned int NumberOfEntriesInLine( NUMBER_NODES_PER_ELEMENT );
	return ( (++NumberOfEntriesInLine) * m_ListOfElemets.size() );
}


void GroupOfTriangles::getInfo() {

	std::cout << "*********************************" << std::endl;
	std::cout << "Type: " << "Group Of Triangles" << std::endl;
	std::cout << "Index: " << m_Index << std::endl;
	std::cout << "Name: " << m_Name << std::endl;
	std::cout << "# Elements: " << m_ListOfElemets.size() << std::endl;
	std::cout << "Update Priority: " << m_Condition->getUpdatePriority() << std::endl;


	if ( isGroupReady() )
		m_Condition.get()->printInformation();

	std::cout << std::endl;
}

void GroupOfTriangles::printElementsAccordingToVtkFormat
								( std::streambuf* OutputBuffer ) {
	for ( auto Iterator = m_ListOfElemets.begin();
		  Iterator != m_ListOfElemets.end();
		  ++Iterator ) {

		print( std::to_string( NUMBER_NODES_PER_ELEMENT )
			 + " "
			 + std::to_string( Iterator->get()->getFirstNode()->getGlobalIndex())
			 + " "
			 + std::to_string( Iterator->get()->getSecondNode()->getGlobalIndex())
			 + " "
			 + std::to_string(Iterator->get()->getThirdNode()->getGlobalIndex()),
			   OutputBuffer );

	}
}

void GroupOfTriangles::printElementsTypeAccordingToVtkFormat
								( std::streambuf* OutputBuffer ) {
	for ( auto Iterator = m_ListOfElemets.begin();
			  Iterator != m_ListOfElemets.end();
			  ++Iterator ) {

		print( std::to_string(Iterator->get()->getElementType()),
			   OutputBuffer );
		}
}
