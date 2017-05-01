/*
 * Matrix.h
 *
 *  Created on: Apr 3, 2017
 *      Author: ravil
 */

#include "Vector.h"
#include "TypeDef.h"

#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix {
public:
	Matrix();
	Matrix( const Matrix& aMatrix );
	Matrix( unsigned int Rows, unsigned int Columns );
	virtual ~Matrix();


	double operator ()( unsigned int Row, unsigned int Column ) const;
	double& operator()( unsigned int Row, unsigned int Column );
	const Matrix& operator=( const Matrix& aMatrix );
	Matrix operator*( const Matrix& aMatrix ) const;
	Vector operator*( const Vector& aVector ) const;
	Matrix operator*( double Constant ) const;
	friend Matrix operator*( double Constant, const Matrix& aMatrix );


	Matrix getInverseMatrix();
	Matrix getInverseMatrix() const;
	double getMatrixDeterminant();


	void assignMatrix( const Matrix& aMatrix );
	unsigned int getNumberOfRows() const;
	unsigned int getNumberOfStrings() const;
	void resize( unsigned int Rows, unsigned int Columns );
	void setStringToZero( unsigned int aRow );
	void clear();
	void print();

private:
	Matrix( boostMatrix aBoostMatrix );

	boostMatrix m_Matrix;
	double m_Determinant;
	bool m_isDeterminantComputed;
};

Matrix operator*( double Constant, const Matrix& aMatrix );

#endif /* MATRIX_H_ */
