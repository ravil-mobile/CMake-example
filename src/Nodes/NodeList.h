/*
 * NodeList.h
 *
 *  Created on: Mar 27, 2017
 *      Author: ravil
 */

#include <vector>
#include <memory>
#include "../Supplements/Printable.h"

class Vector;
class Node;

#ifndef NODES_NODELIST_H_
#define NODES_NODELIST_H_

class NodeList : private Printable {
public:
	NodeList();
	virtual ~NodeList();

	bool isListEmpty() const;


	std::shared_ptr<const Node> getNode( unsigned int Index ) const;
	unsigned int getNumberOfNodes() const;


	void setNode( std::shared_ptr<Node> aNode);
	void setNode( std::vector<double> Container );


	void printCoordinatesInfo(std::streambuf* OutputBuffer = std::cout.rdbuf());
	void printTemperatureInfo(std::streambuf* OutputBuffer = std::cout.rdbuf());


	void adjustStream() const;
	void resetStreamByDefault() const;

	void setRightHandSideAsTemperature( const Vector& );


private:
	std::vector<std::shared_ptr<Node>> m_List;

	// Forbidden operation:
	NodeList( const NodeList& aList );
	const NodeList& operator=( const NodeList& aList );

};



#endif /* NODES_NODELIST_H_ */
