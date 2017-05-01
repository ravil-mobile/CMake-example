/*
 * PointElementType.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: ravil
 */

#include "PointElementType.h"

const ElementType PointElementType::m_Type = POINT;


PointElementType::PointElementType() {
	// TODO Auto-generated constructor stub

}


PointElementType::~PointElementType() {
	// TODO Auto-generated destructor stub
}


PointElementType::PointElementType(const PointElementType& anElement)
					: AbstractElementType( anElement.m_GlobalElementIndex ),
					  m_FirstNode( anElement.m_FirstNode ){
}


PointElementType& PointElementType::operator =(
		const PointElementType& anElement) {
	m_GlobalElementIndex = anElement.m_GlobalElementIndex;
	m_FirstNode = anElement.m_FirstNode;
	return *this;
}


PointElementType::PointElementType(unsigned int Index,
		std::shared_ptr<const Node> FirstNode)
										: AbstractElementType( Index ),
										  m_FirstNode( FirstNode ) {

}


void PointElementType::setFirstNode
						(std::shared_ptr<const Node> FirstNode) {
	m_FirstNode = FirstNode;
}


std::shared_ptr<const Node> PointElementType::getFirstNode() const {
	return m_FirstNode;
}


int PointElementType::getElementType() const {
	return m_Type;
}
