/*
 * PointElementType.h
 *
 *  Created on: Mar 29, 2017
 *      Author: ravil
 */

#ifndef ELEMENTS_POINTELEMENTTYPE_H_
#define ELEMENTS_POINTELEMENTTYPE_H_

#include "../Elements/AbstractElementType.h"

#include "../Nodes/Node.h"
#include <memory>


class PointElementType: public AbstractElementType {
public:
	PointElementType();
	virtual ~PointElementType();

	PointElementType( const PointElementType& anElement );
	PointElementType& operator=( const PointElementType& anElement );

	PointElementType( unsigned int Index,
						   std::shared_ptr<const Node> FirstNode );

	void setFirstNode( std::shared_ptr<const Node> FirstNode );
	std::shared_ptr<const Node> getFirstNode() const;
	int getElementType() const;

private:
	std::shared_ptr<const Node> m_FirstNode;

	static const ElementType m_Type;
};

#endif /* ELEMENTS_POINTELEMENTTYPE_H_ */
