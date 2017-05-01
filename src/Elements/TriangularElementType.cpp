/*
 * TriangularElementType.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: ravil
 */

#include "../Elements/TriangularElementType.h"

const ElementType TriangularElementType::m_Type = TRIANGLE;
const double TriangularElementType::m_ReferenceElementArea = 0.5;



TriangularElementType::TriangularElementType() {
	// TODO Auto-generated constructor stub

}


TriangularElementType::~TriangularElementType() {
	// TODO Auto-generated destructor stub
}


TriangularElementType::TriangularElementType(
		const TriangularElementType& anElement)
				: AbstractElementType( anElement.m_GlobalElementIndex ),
				  m_FirstNode( anElement.m_FirstNode ),
				  m_SecondNode( anElement.m_SecondNode ),
				  m_ThirdNode( anElement.m_ThirdNode ) {
}


TriangularElementType& TriangularElementType::operator =(
		const TriangularElementType& anElement) {
	m_GlobalElementIndex = anElement.m_GlobalElementIndex;
	m_FirstNode = anElement.m_FirstNode;
	m_SecondNode = anElement.m_SecondNode;
	m_ThirdNode = anElement.m_ThirdNode;
	return *this;
}


TriangularElementType::TriangularElementType
									( unsigned int Index,
									  std::shared_ptr<const Node> FirstNode,
									  std::shared_ptr<const Node> SecondNode,
									  std::shared_ptr<const Node> ThirdNode)
							: AbstractElementType( Index ),
							  m_FirstNode( FirstNode ),
							  m_SecondNode( SecondNode ),
							  m_ThirdNode( ThirdNode ) {

}

void TriangularElementType::setFirstNode
					(std::shared_ptr<const Node> FirstNode) {
	m_FirstNode = FirstNode;
}

void TriangularElementType::setSecondNode
					(std::shared_ptr<const Node> SecondNode) {
	m_SecondNode = SecondNode;
}

void TriangularElementType::setThirdNode
					(std::shared_ptr<const Node> ThirdNode) {
	m_ThirdNode = ThirdNode;
}

std::shared_ptr<const Node> TriangularElementType::getFirstNode() const {
	return m_FirstNode;
}

std::shared_ptr<const Node> TriangularElementType::getSecondNode() const {
	return m_SecondNode;
}

std::shared_ptr<const Node> TriangularElementType::getThirdNode() const {
	return m_ThirdNode;
}


Vector TriangularElementType::getFirstBasisReferenceGradient() const {
	Vector FirstGadient(2);
	FirstGadient(0) = -1.0;
	FirstGadient(1) = -1.0;
	return FirstGadient;
}


Vector TriangularElementType::getSecondBasisReferenceGradient() const {
	Vector SecondGadient(2);
	SecondGadient(0) = 1.0;
	SecondGadient(1) = 0.0;
	return SecondGadient;
}


Vector TriangularElementType::getThirdBasisReferenceGradient() const {
	Vector ThirdGadient(2);
	ThirdGadient(0) = 0.0;
	ThirdGadient(1) = 1.0;
	return ThirdGadient;
}

double TriangularElementType::getReferenceElementArea() const {
	return m_ReferenceElementArea;
}

int TriangularElementType::getElementType() const {
	return m_Type;
}
