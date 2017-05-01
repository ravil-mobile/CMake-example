/*
 * LinearElementType.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: ravil
 */

#include "../Elements/LinearElementType.h"

const ElementType LinearElementType::m_Type = LINE;


LinearElementType::LinearElementType() {
	// TODO Auto-generated constructor stub

}

LinearElementType::~LinearElementType() {
	// TODO Auto-generated destructor stub
}

LinearElementType::LinearElementType( unsigned int Index,
									  std::shared_ptr<const Node> FirstNode,
									  std::shared_ptr<const Node> SecondNode )
							: AbstractElementType( Index ),
							  m_FirstNode( FirstNode ),
							  m_SecondNode( SecondNode ) {
}


LinearElementType::LinearElementType(const LinearElementType& anElement)
						: AbstractElementType( anElement.m_GlobalElementIndex ),
						  m_FirstNode( anElement.m_FirstNode ),
						  m_SecondNode( anElement.m_SecondNode ) {
}


LinearElementType& LinearElementType::operator =(
		const LinearElementType& anElement) {
	m_GlobalElementIndex = anElement.m_GlobalElementIndex;
	m_FirstNode = anElement.m_FirstNode;
	m_SecondNode = anElement.m_SecondNode;
	return *this;
}


void LinearElementType::setFirstNode
						( std::shared_ptr<const Node> FirstNode ) {
	m_FirstNode = FirstNode;
}

void LinearElementType::setSecondNode
						( std::shared_ptr<const Node> SecondNode ) {
	m_SecondNode = SecondNode;
}


std::shared_ptr<const Node> LinearElementType::getFirstNode() const {
	return m_FirstNode;
}


std::shared_ptr<const Node> LinearElementType::getSecondNode() const {
	return m_SecondNode;
}


int LinearElementType::getElementType() const {
	return m_Type;
}
