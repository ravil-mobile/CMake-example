/*
 * AbstractElementCondition.h
 *
 *  Created on: Mar 21, 2017
 *      Author: ravil
 */

#include "../Elements/ElementType.h"
#include <iostream>
#include <memory>
#include <vector>

#include "../LinearAlgebra/Matrix.h"
#include "../LinearAlgebra/Vector.h"

#include "UpdatePrioruty.h"

#include "../Elements/LinearElementType.h"

class PointElementType;
//class LinearElementType;
class TriangularElementType;

#ifndef CONDITIONS_ABSTRACTCONDITION_H_
#define CONDITIONS_ABSTRACTCONDITION_H_



class AbstractCondition {
public:
	AbstractCondition();
	AbstractCondition( std::shared_ptr<Matrix> GlobalStiffnessMatrix,
					   std::shared_ptr<Matrix> MassMatrix,
					   std::shared_ptr<Vector> RightHandSide );

	virtual ~AbstractCondition() = 0;

	virtual void updateLinearSystem
				( std::vector<std::shared_ptr<const PointElementType>> );

	virtual void updateLinearSystem
				( std::vector<std::shared_ptr<const LinearElementType>> );


	virtual void updateLinearSystem
				( std::vector<std::shared_ptr<const TriangularElementType>> );

	// Garbage collector
	void updateLinearSystem(...);


	void setGlobalStiffnessMatrix( std::shared_ptr<Matrix> GlobalStiffnessMatrix );
	void setMassMatrix( std::shared_ptr<Matrix> MassMatrix );
	void setRightHandSide( std::shared_ptr<Vector> RightHandSide );

	virtual Priority getUpdatePriority() = 0;

	virtual void printInformation() = 0;

protected:

	// Error collector
	void notReadyForUpdate();

	std::shared_ptr<Matrix> m_GlobalStiffnessMatrix;
	std::shared_ptr<Matrix > m_MassMatrix;
	std::shared_ptr<Vector> m_RightHandSide;
};
#endif /* CONDITIONS_ABSTRACTELEMENTCONDITION_H_ */
