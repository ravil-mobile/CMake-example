/*
 * Vector.cpp
 *
 *  Created on: Apr 3, 2017
 *      Author: ravil
 */

#include "Vector.h"
#include "TypeDef.h"


Vector::Vector() {
	// TODO Auto-generated constructor stub

}


Vector::Vector( unsigned int Rows ) : m_Vector( Rows ),
								  m_ReferenceCounter( Rows ) {
}


Vector::Vector( const Vector& aVector ) {

	m_Vector.resize( aVector.m_Vector.size() );
	m_ReferenceCounter.resize( aVector.m_ReferenceCounter.size() );

	for( unsigned int i = 0; i < m_Vector.size(); ++i ) {
		m_Vector(i) = aVector(i);
		m_ReferenceCounter(i) = aVector.m_ReferenceCounter(i);
	}
}


Vector::~Vector() {
	// TODO Auto-generated destructor stub
}


double Vector::operator ()( unsigned int Row ) const {
	return m_Vector( Row );
}


double& Vector::operator ()( unsigned int Row ) {
	return m_Vector( Row );
}

const Vector& Vector::operator =(const Vector& aVector) {

	// Check is the size of the input and the inner vectors are the same
	bool isVectorSizeNotEqual = bool( m_Vector.size() - aVector.m_Vector.size() );

	if ( __builtin_expect( isVectorSizeNotEqual, false ) ) {
		int Error(1);
		throw Error;
	}

	// Copy all elements to the inner vector
	for( unsigned int i = 0; i < m_Vector.size(); ++i ) {
		m_Vector(i) = aVector(i);
		m_ReferenceCounter(i) = aVector.getVectorReferenceCounter(i);
	}
	return *this;
}


double Vector::operator*( const Vector& aVector ) const {
	return boost::numeric::ublas::inner_prod( m_Vector, aVector.m_Vector );
}


double vectorInnerProduct(const Vector& FirstVector,
						  const Vector& SecondVector) {

	return boost::numeric::ublas::inner_prod
					( FirstVector.m_Vector, SecondVector.m_Vector );
}



Vector Vector::operator *(double Constant) const {
	boostVector Product = m_Vector;
	Product = Constant * Product;
	return Vector( Product );
}


Vector operator *(double Constant, const Vector& aVector) {
	boostVector Product = aVector.m_Vector;
	Product = Constant * Product;
	return Vector( Product );
}


void Vector::assignVector( const Vector& aVector ) {

	m_Vector.resize( aVector.m_Vector.size() );

	// Copy all elements to the inner vector
	for( unsigned int i = 0; i < m_Vector.size(); ++i ) {
		m_Vector(i) = aVector(i);
		m_ReferenceCounter(i) = aVector.getVectorReferenceCounter(i);

	}
}


unsigned int Vector::getSize() const {
	return m_Vector.size();
}



void Vector::resize( unsigned int Rows ) {
	m_Vector.resize( Rows );
	m_ReferenceCounter.resize( Rows );

	for ( unsigned int i = 0; i < Rows; ++i ) {
		m_Vector(i) = 0.0;
		m_ReferenceCounter(i) = 0.0;
	}
}



void Vector::clear() {
	m_Vector.clear();
	m_ReferenceCounter.clear();

	unsigned int Rows = m_Vector.size();
	for ( unsigned int i = 0; i < Rows; ++i ) {
		m_Vector(i) = 0.0;
		m_ReferenceCounter(i) = 0.0;
	}
}



Vector::Vector( boostVector aBoostVector ) {
	m_Vector = aBoostVector;

	unsigned int VectorSize = aBoostVector.size();

	// Set m_ReferenceCounter as a null vector
	m_ReferenceCounter.resize( VectorSize );
	for ( unsigned int i = 0; i < VectorSize; ++i ) {
		m_ReferenceCounter(i) = 0.0;
	}

}


void Vector::print() {
	std::cout << m_Vector << std::endl;
}


double Vector::getVectorReferenceCounter(unsigned int VectorElement) const {
	return m_ReferenceCounter( VectorElement );
}


void Vector::incrementVectorReferenceCounter(unsigned int VectorElement) {
	++m_ReferenceCounter( VectorElement );
}


