/*
 * FirstBoundaryCondition.h
 *
 *  Created on: Mar 30, 2017
 *      Author: ravil
 */

#ifndef CONDITIONS_SHT_BC_FIRSTTYPE_H_
#define CONDITIONS_SHT_BC_FIRSTTYPE_H_

#include "AbstractCondition.h"
#include "UpdatePrioruty.h"

class SHT_BC_FirstType: public AbstractCondition {
public:
	SHT_BC_FirstType();
	SHT_BC_FirstType( double WallTemperature,
				  std::shared_ptr<Matrix> GlobalStiffnessMatrix = 0,
				  std::shared_ptr<Matrix> MassMatrix = 0,
				  std::shared_ptr<Vector> RightHandSide = 0 );

	virtual ~SHT_BC_FirstType();

	using AbstractCondition::updateLinearSystem;
	virtual void updateLinearSystem
			( std::vector<std::shared_ptr<const PointElementType>> );

	virtual void updateLinearSystem
			( std::vector<std::shared_ptr<const LinearElementType>> );

	Priority getUpdatePriority();

	void setWallTemperature( double Temperature );
	double getWallTemperature();
	void printInformation();

private:
	void updateGlobalStiffnessMatrix( std::shared_ptr<const LinearElementType> );
	void updateRightHandSide( std::shared_ptr<const LinearElementType> );

	double m_WallTemperature;

};

#endif /* CONDITIONS_SHT_BC_FIRSTTYPE_H_ */
