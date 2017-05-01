/*
 * GroupTriangles.h
 *
 *  Created on: Mar 26, 2017
 *      Author: ravil
 */

#include "Group.h"
#include "../Elements/TriangularElementType.h"

class NodeList;

#ifndef GROUPOFTRIANGLES_H_
#define GROUPOFTRIANGLES_H_


class GroupOfTriangles: public Group {
public:
	GroupOfTriangles();
	GroupOfTriangles( unsigned int Index,
					  std::string Name,
					  std::shared_ptr<const NodeList> Nodes );

	virtual ~GroupOfTriangles();

	void insertElement( std::vector<unsigned int> Bundle );
	void updateLinearSystem();

	unsigned int getNumberOfElements();
	unsigned int getNumberOfEntriesInVtkTable();
	void printElementsAccordingToVtkFormat
				( std::streambuf* OutputBuffer = std::cout.rdbuf() );
	void printElementsTypeAccordingToVtkFormat
				( std::streambuf* OutputBuffer = std::cout.rdbuf() );

	void getInfo();

private:
	std::vector<std::shared_ptr<const TriangularElementType>> m_ListOfElemets;

	static const unsigned int NUMBER_NODES_PER_ELEMENT;
};

#endif /* GROUPOFTRIANGLES_H_ */
