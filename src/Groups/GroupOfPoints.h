/*
 * GroupOfDots.h
 *
 *  Created on: Mar 26, 2017
 *      Author: ravil
 */

#ifndef GROUPOFPOINTS_H_
#define GROUPOFPOINTS_H_

#include "Group.h"
#include "../Elements/PointElementType.h"

class GroupOfPoints: public Group {
public:
	GroupOfPoints();
	GroupOfPoints( unsigned int Index,
				 std::string Name,
				 std::shared_ptr<const NodeList> Nodes );

	virtual ~GroupOfPoints();

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
	std::vector<std::shared_ptr<const PointElementType>> m_ListOfElemets;

	static const unsigned int NUMBER_NODES_PER_ELEMENT;
};

#endif /* GROUPOFPOINTS_H_ */
