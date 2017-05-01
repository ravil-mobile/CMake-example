/*
 * NodeList.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: ravil
 */

#include "../Nodes/NodeList.h"
#include "../Nodes/Node.h"
#include "../LinearAlgebra/Matrix.h"
#include "../LinearAlgebra/Vector.h"

#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>


NodeList::NodeList() {
	// TODO Auto-generated constructor stub

}


NodeList::NodeList(const NodeList& aList) {
	this->m_List = aList.m_List;
}


NodeList::~NodeList() {
	// TODO Auto-generated destructor stub
}


std::shared_ptr<const Node> NodeList::getNode
							( unsigned int Index ) const {
	return m_List[ Index ];
}


void NodeList::setNode( std::shared_ptr<Node> aNode ) {
	m_List.push_back(aNode);
}


void NodeList::setNode( std::vector<double> Container ) {
	std::shared_ptr<Node> aNode( new Node( int(Container[0]),
										   	   Container[1],
											   Container[2],
											   Container[3] ) );
	//aNode->getInfo();
	m_List.push_back(aNode);
}



bool NodeList::isListEmpty() const {
	return m_List.empty();
}


void NodeList::printCoordinatesInfo( std::streambuf* OutputBuffer ) {

	// Adjust precision of the output stream
	adjustStream();


	// Print coordinates of nodes according to the VTK format
	for( auto Iterator = m_List.begin();
		 Iterator != m_List.end();
		 ++Iterator ) {

		print( std::to_string(Iterator->get()->getCoordianteX()) + " "
			   + std::to_string(Iterator->get()->getCoordianteY()) + " "
			   + std::to_string(Iterator->get()->getCoordianteZ()),
			   OutputBuffer );

	}


	// Restore all setting of the output stream by default
	resetStreamByDefault();

	// Pint an empty string
	print( "", OutputBuffer);
}


void NodeList::printTemperatureInfo( std::streambuf* OutputBuffer ) {

	// Print coordinate point header according to the VTK format
	print( "SCALARS Temperature float", OutputBuffer );
	print( "LOOKUP_TABLE default", OutputBuffer );


	// Adjust precision of the output stream
	adjustStream();


	// Print coordinates of nodes according to the VTK format
	for( auto Iterator = m_List.begin();
		 Iterator != m_List.end();
		 ++Iterator ) {
		print( std::to_string(Iterator->get()->getTemperature()),
			   OutputBuffer );
	}


	// Restore all setting of the output stream by default
	resetStreamByDefault();


	// Pint an empty string
	print( "", OutputBuffer);
}


unsigned int NodeList::getNumberOfNodes() const {
	return m_List.size();
}


void NodeList::adjustStream() const {
	std::cout << std::showpoint << std::setprecision(4);
}


void NodeList::resetStreamByDefault() const {
	std::cout << std::noshowpoint;
}



const NodeList& NodeList::operator =(const NodeList& aList) {
	return *this;
}


void NodeList::setRightHandSideAsTemperature
					( const Vector& Temperature ) {

	for( auto Iterator = m_List.begin();
		 Iterator < m_List.end();
		 ++Iterator ) {

		Iterator->get()->setTemperature(
				Temperature(Iterator->get()->getGlobalIndex()));
	}
}
