/*
 * AbstractElementType.h
 *
 *  Created on: Mar 21, 2017
 *      Author: ravil
 */


#include "ElementType.h"

#ifndef ELEMENTTYPES_ABSTRACTELEMENTTYPE_H_
#define ELEMENTTYPES_ABSTRACTELEMENTTYPE_H_

class AbstractElementType {
public:
	AbstractElementType();
	AbstractElementType( const AbstractElementType& anElement );
	AbstractElementType& operator=( const AbstractElementType& anElement );

	AbstractElementType( unsigned int Index );

	virtual ~AbstractElementType() = 0;

	virtual int getElementType() const = 0;

protected:
	unsigned int m_GlobalElementIndex;

};

#endif /* ELEMENTTYPES_ABSTRACTELEMENTTYPE_H_ */
