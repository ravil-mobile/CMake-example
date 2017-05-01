/*
 * TriangularElementType.h
 *
 *  Created on: Mar 21, 2017
 *      Author: ravil
 */

#ifndef ELEMENTTYPES_TRIANGULARELEMENTTYPE_H_
#define ELEMENTTYPES_TRIANGULARELEMENTTYPE_H_

#include "../Elements/AbstractElementType.h"
#include "../Nodes/Node.h"
#include "../LinearAlgebra/Matrix.h"
#include "../LinearAlgebra/Vector.h"
#include <memory>

class TriangularElementType: public AbstractElementType {
public:
	TriangularElementType();
	TriangularElementType( const TriangularElementType& anElement );
	TriangularElementType( unsigned int Index,
						   std::shared_ptr<const Node> FirstNode,
			   	   	   	   std::shared_ptr<const Node> SecondNode,
						   std::shared_ptr<const Node> ThirdNode);

	TriangularElementType& operator=( const TriangularElementType& anElement );

	virtual ~TriangularElementType();

	void setFirstNode( std::shared_ptr<const Node> FirstNode );
	void setSecondNode( std::shared_ptr<const Node> SecondNode );
	void setThirdNode( std::shared_ptr<const Node> ThirdNode );

	std::shared_ptr<const Node> getFirstNode() const;
	std::shared_ptr<const Node> getSecondNode() const;
	std::shared_ptr<const Node> getThirdNode() const;
	Vector getFirstBasisReferenceGradient() const;
	Vector getSecondBasisReferenceGradient() const;
	Vector getThirdBasisReferenceGradient() const;
	double getReferenceElementArea() const;

	int getElementType() const;

private:
	std::shared_ptr<const Node> m_FirstNode;
	std::shared_ptr<const Node> m_SecondNode;
	std::shared_ptr<const Node> m_ThirdNode;

	static const ElementType m_Type;
	static const double m_ReferenceElementArea;
};

#endif /* ELEMENTTYPES_TRIANGULARELEMENTTYPE_H_ */
