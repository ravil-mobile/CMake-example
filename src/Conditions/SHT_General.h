/*
 * GeneralCondition.h
 *
 *  Created on: Mar 21, 2017
 *      Author: ravil
 */

#include "AbstractCondition.h"

#ifndef CONDITIONS_GENERAL_C_SHT_H_
#define CONDITIONS_GENERAL_C_SHT_H_



class SHT_General: public AbstractCondition {
public:
	SHT_General();
	SHT_General( double Temperature,
				  std::shared_ptr<Matrix> GlobalStiffnessMatrix = 0,
				  std::shared_ptr<Matrix> MassMatrix = 0,
				  std::shared_ptr<Vector> RightHandSide = 0 );

	virtual ~SHT_General();


	using AbstractCondition::updateLinearSystem;
	virtual void updateLinearSystem
				( std::vector<std::shared_ptr<const TriangularElementType>> );

	void setTemperature( double Temperature );

	Priority getUpdatePriority();
	double getTemperature();

	virtual void printInformation();

private:
	void updateGlobalStiffnessMatrix
					( std::shared_ptr<const TriangularElementType> );

	Matrix computeLocalStiffnessMatrix
					( std::shared_ptr<const TriangularElementType> );


	double m_Temperature;
};

#endif /* CONDITIONS_GENERAL_C_SHT_H_ */
