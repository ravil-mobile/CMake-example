/*
 * ThirdBoudaryCondition.h
 *
 *  Created on: Mar 21, 2017
 *      Author: ravil
 */

#include "AbstractCondition.h"

#ifndef CONDITIONS_THIRD_BC_SHT_H_
#define CONDITIONS_THIRD_BC_SHT_H_


class SHT_BC_ThirdType: public AbstractCondition {
public:
	SHT_BC_ThirdType();
	SHT_BC_ThirdType( double EnvironmentTemperature,
				  double HeatTransfer,
				  double ConductivityCoefficient,
				  std::shared_ptr<Matrix> GlobalStiffnessMatrix = 0,
				  std::shared_ptr<Matrix> MassMatrix = 0,
				  std::shared_ptr<Vector> RightHandSide = 0 );

	virtual ~SHT_BC_ThirdType();

	using AbstractCondition::updateLinearSystem;
	virtual void updateLinearSystem
			( std::vector<std::shared_ptr<const LinearElementType>> );

	Priority getUpdatePriority();

	void setEnvironmentTemperature( double EnvironmentTemperature );
	void setHeatTransfer( double HeatTransfer );
	void setConductivityCoefficient( double ConductivityCoefficient );


	double getEnvironmentTemperature();
	double getHeatTransfer();
	double getConductivityCoefficient();

	virtual void printInformation();

private:

	void updateGlobalStiffnessMatrix
					( std::shared_ptr<const LinearElementType> anElement,
					  const Matrix& LocalReferenceStiffnessMatrix,
					  const double Length );

	void updateRightHandSide
					( std::shared_ptr<const LinearElementType> anElement,
						  const Matrix& LocalReferenceStiffnessMatrix,
						  const double Length );

	void computeScaleCoefficient();


	double m_EnvironmentTemperature;
	double m_HeatTransfer;
	double m_ConductivityCoefficient;
	double m_ScaleCoefficient;

};

#endif /* CONDITIONS_THIRD_BC_SHT_H_ */
