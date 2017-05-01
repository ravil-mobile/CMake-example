/*
 * Node.h
 *
 *  Created on: Mar 27, 2017
 *      Author: ravil
 */

#ifndef NODES_NODE_H_
#define NODES_NODE_H_

class Node {
public:
	Node();
	Node( unsigned int, double, double, double );
	Node( const Node& aNode);
	~Node();

	unsigned int getGlobalIndex() const;
	double getCoordianteX() const;
	double getCoordianteY() const;
	double getCoordianteZ() const;
	double getTemperature() const;
	void printCoordinates() const;
	void printTemperature() const;

	void setGlobalIndex( unsigned int );
	void setCoordinateX( double );
	void setCoordinateY( double );
	void setCoordinateZ( double );
	void setTemperature( double );

private:
	unsigned int m_GlobalIndex;
	double m_CoordinateX;
	double m_CoordinateY;
	double m_CoordinateZ;
	double m_Temperature;

	static const unsigned int DISPLACEMENT;

	// Forbidden operation:
	const Node& operator=( const Node& aNode ) { return *this; };

};

#endif /* NODES_NODE_H_ */
