/*
 * SecondBoundaryCondition.h
 *
 *  Created on: Mar 30, 2017
 *      Author: ravil
 */

#ifndef CONDITIONS_SHT_BC_SECONDTYPE_H_
#define CONDITIONS_SHT_BC_SECONDTYPE_H_

#include "AbstractCondition.h"

class SHT_BC_SecondType: public AbstractCondition {
public:
	SHT_BC_SecondType();
	SHT_BC_SecondType( double Flux,
				  std::shared_ptr<Matrix> GlobalStiffnessMatrix = 0,
				  std::shared_ptr<Matrix> MassMatrix = 0,
				  std::shared_ptr<Vector> RightHandSide = 0 );

	virtual ~SHT_BC_SecondType();


	using AbstractCondition::updateLinearSystem;
	virtual void updateLinearSystem
			( std::vector<std::shared_ptr<const LinearElementType>> );

	Priority getUpdatePriority();

	void setFlux( double Flux );
	double getFlux();
	virtual void printInformation();

private:

	void updateRightHandSide( std::shared_ptr<const LinearElementType> anElement,
			  	  	  	  	  const Matrix& LocalReferenceStiffnessMatrix,
							  const double Length);

	double m_Flux;
};

#endif /* CONDITIONS_SHT_BC_SECONDTYPE_H_ */
