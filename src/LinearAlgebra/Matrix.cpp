/*
 * Mesh.cpp
 *
 *  Created on: Apr 3, 2017
 *      Author: ravil
 */

#include "Matrix.h"
#include "TypeDef.h"

Matrix::Matrix() : m_Matrix( 0, 0 ),
				   m_Determinant(0.0),
				   m_isDeterminantComputed(false) {
	// TODO Auto-generated constructor stub

}


Matrix::Matrix( unsigned int Rows, unsigned int Columns )
								: m_Matrix( Rows, Columns ),
								  m_Determinant(0.0),
								  m_isDeterminantComputed(false) {

}

Matrix::Matrix( const Matrix& aMatrix )
					: m_Determinant(aMatrix.m_Determinant),
					m_isDeterminantComputed(aMatrix.m_isDeterminantComputed) {

	// Copy each elements from the input matrix to the inner Matrix
	unsigned int Rows = aMatrix.getNumberOfRows();
	unsigned int Columns = aMatrix.getNumberOfStrings();

	m_Matrix.resize( Rows, Columns );

	for ( unsigned int i = 0; i < Rows; ++i ) {
		for( unsigned int j = 0; j < Columns; ++j ) {
			m_Matrix(i,j) = aMatrix(i,j);
		}
	}
}


Matrix::Matrix( boostMatrix aBoostMatrix ) : m_Matrix( aBoostMatrix ),
										     m_Determinant(0.0),
		  	  	  	  	  	  	  	  	  	 m_isDeterminantComputed(false) {
}


Matrix::~Matrix() {
	// TODO Auto-generated destructor stub
}



double Matrix::operator ()( unsigned int Row, unsigned int Column ) const {
	return m_Matrix( Row, Column );
}


double& Matrix::operator ()(unsigned int Row, unsigned int Column) {
	return m_Matrix( Row, Column );
}



const Matrix& Matrix::operator=(const Matrix& aMatrix) {

	// Check if the matrixes have the same dimension
	bool isRowSizeNotEqual = bool( m_Matrix.size1() - aMatrix.m_Matrix.size1() );
	bool isColumnSizeNotEqual = bool( m_Matrix.size2() - aMatrix.m_Matrix.size2() );
	bool isMatricesNotEqual = bool( isColumnSizeNotEqual + isRowSizeNotEqual );

	if ( __builtin_expect( isMatricesNotEqual, false ) ) {
		int Error(1);
		throw Error;
	}

	// Copy each elements from the input matrix to the inner Matrix
	unsigned int Rows = aMatrix.getNumberOfRows();
	unsigned int Columns = aMatrix.getNumberOfStrings();

	for ( unsigned int i = 0; i < Rows; ++i ) {
		for( unsigned int j = 0; j < Columns; ++j ) {
			m_Matrix(i,j) = aMatrix(i,j);
		}
	}

	// Copy the additional information
	m_Determinant = aMatrix.m_Determinant;
	m_isDeterminantComputed = aMatrix.m_isDeterminantComputed;


	return *this;
}


Matrix Matrix::operator *(const Matrix& aMatrix) const {

	// If the number of rows and columns is different
	// throw an error
	if ( m_Matrix.size2() != aMatrix.m_Matrix.size1() ) {
		int Error(1);
		throw Error;
	}

	boostMatrix Product( m_Matrix.size1(), aMatrix.m_Matrix.size2()  ) ;
	Product = boost::numeric::ublas::prod( m_Matrix, aMatrix.m_Matrix );

	return Matrix( Product );
}


Vector Matrix::operator *(const Vector& aVector) const {

	// If the number of rows and columns is different
	// throw an error

	if ( m_Matrix.size2() != aVector.m_Vector.size() ) {
		int Error(1);
		throw Error;
	}

	boostVector Product( aVector.m_Vector.size() );

	Product = boost::numeric::ublas::prod( m_Matrix, aVector.m_Vector );
	return Vector( Product );
}



Matrix Matrix::operator *(double Constant) const {
	boostMatrix Product = m_Matrix;
	Product = Constant * Product;
	return Matrix( Product );
}


Matrix operator*( double Constant, const Matrix& aMatrix ) {
	boostMatrix Product = aMatrix.m_Matrix;
	Product = Constant * Product;
	return Matrix( Product );
}


Matrix Matrix::getInverseMatrix() {

	// The function compute both the inverse matrix
	// and its determinant


	// Check if the matrix is not square
	bool isMatrixRectangular
			= bool( m_Matrix.size1() - m_Matrix.size2() );

	if ( __builtin_expect( isMatrixRectangular, false ) ) {
		int Error(1);
		throw Error;
	}



	// Create a permutation matrix
	boostPermutationMatrix PermutationMatrix( m_Matrix.size1() );


	 // Create the inverse matrix and assign the identiry matrix
	boostMatrix InverseMatrix( boostIdentityMatrix(m_Matrix.size1()) );


	// Create a duplicate of the input matrix
	boostMatrix InsituMatrix = m_Matrix;


	//	Make LU factorization
	bool IsMatrixSingular
			= boost::numeric::ublas::lu_factorize(InsituMatrix, PermutationMatrix);


	// Throw an exception if the matrix is singular
	if ( __builtin_expect( IsMatrixSingular, false ) ) {
		int Error(1);
		throw Error;
	}


	//  Make LU substitution
	boost::numeric::ublas::lu_substitute
							(InsituMatrix,PermutationMatrix,InverseMatrix);


	// Compute determinant of the matrix
	m_Determinant = 1.0;
	for (unsigned int i = 0; i < PermutationMatrix.size(); ++i) {
		if (PermutationMatrix(i) != i) {
			m_Determinant *= -1.0;
		}
		m_Determinant *= InsituMatrix(i,i);
	}


	// set the flag that the determinant has been computed
	m_isDeterminantComputed = true;


	return Matrix( InverseMatrix );
}


Matrix Matrix::getInverseMatrix() const {

	// The function compute both the inverse matrix
	// and its determinant


	// Check if the matrix is not square
	bool isMatrixRectangular
			= bool( m_Matrix.size1() - m_Matrix.size2() );

	if ( __builtin_expect( isMatrixRectangular, false ) ) {
		int Error(1);
		throw Error;
	}



	// Create a permutation matrix
	boostPermutationMatrix PermutationMatrix( m_Matrix.size1() );


	 // Create the inverse matrix and assign the identiry matrix
	boostMatrix InverseMatrix( boostIdentityMatrix(m_Matrix.size1()) );


	// Create a duplicate of the input matrix
	boostMatrix InsituMatrix = m_Matrix;


	//	Make LU factorization
	bool IsMatrixSingular
			= boost::numeric::ublas::lu_factorize(InsituMatrix, PermutationMatrix);


	// Throw an exception if the matrix is singular
	if ( __builtin_expect( IsMatrixSingular, false ) ) {
		int Error(1);
		throw Error;
	}


	//  Make LU substitution
	boost::numeric::ublas::lu_substitute
							(InsituMatrix,PermutationMatrix,InverseMatrix);


	return Matrix( InverseMatrix );
}



double Matrix::getMatrixDeterminant() {
	if ( m_isDeterminantComputed == true ) {
		return m_Determinant;
	}
	else {
		getInverseMatrix();
		return m_Determinant;
	}

}


void inverseMatrixAndGetDeterminant(const Matrix& aMatrix,
		double& Determinant) {
}


void Matrix::assignMatrix( const Matrix& aMatrix ) {

	unsigned int Rows = aMatrix.getNumberOfRows();
	unsigned int Columns = aMatrix.getNumberOfStrings();

	m_Matrix.resize( Rows, Columns );

	// Copy each elements from the input matrix to the inner Matrix
	for ( unsigned int i = 0; i < Rows; ++i ) {
		for( unsigned int j = 0; j < Columns; ++j ) {
			m_Matrix(i,j) = aMatrix(i,j);
		}
	}

	// Copy the additional information
	m_Determinant = aMatrix.m_Determinant;
	m_isDeterminantComputed = aMatrix.m_isDeterminantComputed;

}


unsigned int Matrix::getNumberOfRows() const {
	return m_Matrix.size1();
}


unsigned int Matrix::getNumberOfStrings() const {
	return m_Matrix.size2();
}


void Matrix::resize(unsigned int Rows, unsigned int Columns) {
	m_Matrix.resize( Rows, Columns );

	for ( unsigned int i = 0; i < Rows; ++i ) {
		for( unsigned int j = 0; j < Columns; ++j ) {
			m_Matrix(i,j) = 0.0;
		}
	}
}


void Matrix::setStringToZero( unsigned int aRow ) {
	for ( unsigned int i = 0; i < m_Matrix.size2(); ++i ) {
		m_Matrix( aRow, i ) = 0.0;
	}
}


void Matrix::clear() {
	m_Matrix.clear();

	unsigned int Rows = m_Matrix.size1();
	unsigned int Columns = m_Matrix.size2();

	for ( unsigned int i = 0; i < Rows; ++i ) {
		for( unsigned int j = 0; j < Columns; ++j ) {
			m_Matrix(i,j) = 0.0;
		}
	}
}


void Matrix::print() {
	std::cout << m_Matrix << std::endl;
}


