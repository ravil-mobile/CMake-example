/*
 * Vector.h
 *
 *  Created on: Apr 3, 2017
 *      Author: ravil
 */

#include "TypeDef.h"
class Matrix;

#ifndef VECTOR_H_
#define VECTOR_H_

class Vector {
public:
	Vector();
	Vector( const Vector& aVector );
	Vector( unsigned int Rows );
	virtual ~Vector();


	double operator()( unsigned int Row ) const;
	double& operator()( unsigned int Row );
	const Vector& operator=( const Vector& aVector );


	double operator*( const Vector& aVector ) const;
	Vector operator*( double Constant ) const;
	friend Vector operator*( double Constant, const Vector& aVector );
	friend double vectorInnerProduct( const Vector& FirstVector,
			   	   	   	   	   	   	  const Vector& SecondVector );

	void assignVector( const Vector& aVector );
	unsigned int getSize() const;
	void resize( unsigned Rows );
	void clear();
	void print();

	double getVectorReferenceCounter( unsigned int VectorElement ) const;
	void incrementVectorReferenceCounter( unsigned int VectorElement );

	friend class Matrix;

private:
	Vector( boostVector aBoostVector );


	boostVector m_Vector;
	boostVector m_ReferenceCounter;
};


Vector operator*( double Constant, const Vector& aVector );
double vectorInnerProduct( const Vector& FirstVector,
						   const Vector& SecondVector );

#endif /* VECTOR_H_ */
