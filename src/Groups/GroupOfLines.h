/*
 * GroupOfLines.h
 *
 *  Created on: Mar 26, 2017
 *      Author: ravil
 */

#ifndef GROUPOFLINES_H_
#define GROUPOFLINES_H_

#include "Group.h"
#include "../Elements/LinearElementType.h"
class NodeList;

class GroupOfLines: public Group {
public:
	GroupOfLines();
	GroupOfLines( unsigned int Index,
				  std::string Name,
				  std::shared_ptr<const NodeList> Nodes );

	virtual ~GroupOfLines();

	void insertElement( std::vector<unsigned int> Bundle );
	void updateLinearSystem();

	unsigned int getNumberOfElements();
	unsigned int getNumberOfEntriesInVtkTable();
	void printElementsAccordingToVtkFormat
					(std::streambuf* OutputBuffer = std::cout.rdbuf());
	void printElementsTypeAccordingToVtkFormat
					(std::streambuf* OutputBuffer = std::cout.rdbuf());

	void getInfo();

private:

	std::vector<std::shared_ptr<const LinearElementType>> m_ListOfElemets;
	static const unsigned int NUMBER_NODES_PER_ELEMENT;
};

#endif /* GROUPOFLINES_H_ */
