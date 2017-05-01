/*
 * Group.h
 *
 *  Created on: Mar 26, 2017
 *      Author: ravil
 */

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>

#include "../Supplements/Printable.h"


#include "../Conditions/AbstractCondition.h"

class NodeList;

#ifndef GROUP_H_
#define GROUP_H_


class Group : protected Printable {
public:
	Group();
	Group( unsigned int Index,
		   std::string Name,
		   std::shared_ptr<const NodeList> Nodes );

	virtual ~Group() = 0;

	void setIndex( unsigned int Index );
	void setName( std::string Name );


	virtual void insertElement( std::vector<unsigned int> Bundle ) = 0;
	void insertCondition( std::shared_ptr<AbstractCondition> Condition );


	virtual void updateLinearSystem() = 0;


	unsigned int getIndex();
	std::string getName();
	virtual unsigned int getNumberOfElements() = 0;
	virtual unsigned int getNumberOfEntriesInVtkTable() = 0;
	unsigned int getUpdatePriority();
	virtual void getInfo() = 0;


	virtual void printElementsAccordingToVtkFormat
					( std::streambuf* OutputBuffer = std::cout.rdbuf()) = 0;
	virtual void printElementsTypeAccordingToVtkFormat
					( std::streambuf* OutputBuffer = std::cout.rdbuf() ) = 0;

	bool isGroupReady();

protected:
	unsigned int m_Index;
	std::string m_Name;

	std::shared_ptr<const NodeList> m_Nodes;
	std::shared_ptr<AbstractCondition> m_Condition;

};

#endif /* GROUPELEMENTS_H_ */
