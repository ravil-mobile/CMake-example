/*
 * AbstractElementType.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: ravil
 */

#include "../Elements/AbstractElementType.h"


AbstractElementType::AbstractElementType() : m_GlobalElementIndex(0) {
	// TODO Auto-generated constructor stub

}


AbstractElementType::~AbstractElementType() {
	// TODO Auto-generated destructor stub
}


AbstractElementType::AbstractElementType(const AbstractElementType& anElement)
				 : m_GlobalElementIndex( anElement.m_GlobalElementIndex ) {
}


AbstractElementType& AbstractElementType::operator =(
		const AbstractElementType& anElement) {
	m_GlobalElementIndex = anElement.m_GlobalElementIndex;
	return *this;
}


AbstractElementType::AbstractElementType( unsigned int Index )
										: m_GlobalElementIndex( Index ) {
}
