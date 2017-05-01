/*
 * Node.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: ravil
 */

#include "iostream"
#include <iomanip>
#include "Node.h"

const unsigned int Node::DISPLACEMENT = 1;

Node::Node() : m_GlobalIndex( 0.0 ),
			   m_CoordinateX( 0.0 ),
			   m_CoordinateY( 0.0 ),
			   m_CoordinateZ( 0.0 ),
			   m_Temperature( 0.0 )  {

	// TODO Auto-generated constructor stub

}


Node::Node( unsigned int GlobalIndex,
		    double CoordianteX,
			double CoordianteY,
			double CoordianteZ )
					: m_GlobalIndex( GlobalIndex - DISPLACEMENT ),
					  m_CoordinateX( CoordianteX ),
					  m_CoordinateY( CoordianteY ),
					  m_CoordinateZ( CoordianteZ ),
					  m_Temperature( 0.0 ) {
}


Node::Node( const Node& aNode ) {
	m_GlobalIndex = aNode.getGlobalIndex();
	m_CoordinateX = aNode.getCoordianteX();
	m_CoordinateY = aNode.getCoordianteY();
	m_CoordinateZ = aNode.getCoordianteZ();
	m_Temperature = aNode.getTemperature();
}



Node::~Node() {
	// TODO Auto-generated destructor stub
}


unsigned int Node::getGlobalIndex() const {
	return m_GlobalIndex;
}


double Node::getCoordianteX() const {
	return m_CoordinateX;
}


double Node::getCoordianteY() const {
	return m_CoordinateY;
}


double Node::getCoordianteZ() const {
	return m_CoordinateZ;
}


double Node::getTemperature() const {
	return m_Temperature;
}


void Node::setGlobalIndex(unsigned int GlobalIndex) {
	m_GlobalIndex = GlobalIndex - DISPLACEMENT;
}


void Node::setCoordinateX(double CoordinateX) {
	m_CoordinateX = CoordinateX;
}


void Node::setCoordinateY(double CoordinateY) {
	m_CoordinateY = CoordinateY;
}


void Node::setCoordinateZ(double CoordinateZ) {
	m_CoordinateZ = CoordinateZ;
}


void Node::setTemperature(double Temperature) {
	m_Temperature = Temperature;
}


void Node::printCoordinates() const {
	std::cout << m_CoordinateX << " "
			  << m_CoordinateY << " "
			  << m_CoordinateZ
			  << std::endl;
}


void Node::printTemperature() const {
	std::cout << m_Temperature << std::endl;
}


