/*
 * LinearElementType.h
 *
 *  Created on: Mar 21, 2017
 *      Author: ravil
 */

#ifndef ELEMENTTYPES_LINEARELEMENTTYPE_H_
#define ELEMENTTYPES_LINEARELEMENTTYPE_H_

#include "../Elements/AbstractElementType.h"
#include "../Nodes/Node.h"
#include <memory>

class LinearElementType: public AbstractElementType {
public:
	LinearElementType();
	LinearElementType( const LinearElementType& anElement );
	LinearElementType& operator=( const LinearElementType& anElement );

	LinearElementType( unsigned int Index,
					   std::shared_ptr<const Node> FirstNode,
					   std::shared_ptr<const Node> SecondNode );

	virtual ~LinearElementType();

	void setFirstNode( std::shared_ptr<const Node> FirstNode );
	void setSecondNode( std::shared_ptr<const Node> SecondNode );

	std::shared_ptr<const Node> getFirstNode() const;
	std::shared_ptr<const Node> getSecondNode() const;
	int getElementType() const;


private:
	std::shared_ptr<const Node> m_FirstNode;
	std::shared_ptr<const Node> m_SecondNode;

	static const ElementType m_Type;
};

#endif /* ELEMENTTYPES_LINEARELEMENTTYPE_H_ */
