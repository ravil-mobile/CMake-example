/*
 * AbstractElementCondition.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: ravil
 */

#include "AbstractCondition.h"
#include "../Elements/AbstractElementType.h"
#include "../Elements/PointElementType.h"
#include "../Elements/LinearElementType.h"
#include "../Elements/TriangularElementType.h"



AbstractCondition::AbstractCondition() : m_GlobalStiffnessMatrix(0),
										 m_MassMatrix(0),
										 m_RightHandSide(0) {
	// TODO Auto-generated constructor stub

}


AbstractCondition::AbstractCondition(
		std::shared_ptr<Matrix> GlobalStiffnessMatrix,
		std::shared_ptr<Matrix> MassMatrix,
		std::shared_ptr<Vector> RightHandSide)
									  : m_GlobalStiffnessMatrix( GlobalStiffnessMatrix ),
										m_MassMatrix( MassMatrix ),
										m_RightHandSide( RightHandSide ) {
}



AbstractCondition::~AbstractCondition() {
	// TODO Auto-generated destructor stub
}


void AbstractCondition::updateLinearSystem(
		std::vector<std::shared_ptr<const PointElementType>> Points ) {

	// Throw an error calling the garbage collector
	updateLinearSystem();
}


void AbstractCondition::updateLinearSystem(
		std::vector<std::shared_ptr<const LinearElementType>> Lines ) {

	// Throw an error calling the garbage collector
	updateLinearSystem();
}


void AbstractCondition::updateLinearSystem(
		std::vector<std::shared_ptr<const TriangularElementType>> Trinagles ) {

	// Throw an error calling the garbage collector
	updateLinearSystem();
}


void AbstractCondition::updateLinearSystem( ... ) {

	// Garbage collector: if the user call that function
	// it means that there is no appropriate implementation
	// for the boundary conditions and the type of elements that
	// he or she tried to use to update the linear system
	std::cout << "default update implementation" << std::endl;
	int Error(1);
	throw Error;
}


void AbstractCondition::setGlobalStiffnessMatrix(
		std::shared_ptr<Matrix> GlobalStiffnessMatrix ) {
	m_GlobalStiffnessMatrix = GlobalStiffnessMatrix;
}


void AbstractCondition::setMassMatrix(std::shared_ptr<Matrix> MassMatrix ) {
	m_MassMatrix = MassMatrix;
}


void AbstractCondition::setRightHandSide(
		std::shared_ptr<Vector> RightHandSide ) {
	m_RightHandSide = RightHandSide;
}


void AbstractCondition::notReadyForUpdate() {
	// Error collector: if someone call that function
	// it means that some of matrices were not ready to update
	// that means that a pointer to a matrix was equal to zero
	// or the size of an element list was not equal
	// to the matrix size

	int Error(1);
	throw Error;
}
