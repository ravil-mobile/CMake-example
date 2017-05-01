/*
 * Mesh.h
 *
 *  Created on: Mar 26, 2017
 *      Author: ravil
 */

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "../Supplements/Printable.h"
#include "../Conditions/AbstractCondition.h"

class Group;
class NodeList;

#ifndef GROUPLIST_H_
#define GROUPLIST_H_

class GroupList : private Printable {
public:

	GroupList();
	GroupList( std::shared_ptr<NodeList> );

	virtual ~GroupList();

	void insertGroup( std::shared_ptr<Group> aGroup );
	void insertGroup( std::vector<std::string> Container );
	void deleteGroup( unsigned int Index );
	void deleteGroup( std::string Name );
	void printGroupsInfo();
	unsigned int getNumberOfGroups();
	unsigned int getTotalNumberOfElements();
	unsigned int getTotalNumberOfEntries();
	void printElementsAccordingToVtkFormat
						( std::streambuf* OutputBuffer = std::cout.rdbuf() );
	void printElementsTypeAccordingToVtkFormat
						( std::streambuf* OutputBuffer = std::cout.rdbuf() );

	void insertCondition( std::string Name,
						  std::shared_ptr<AbstractCondition> Condition );

	void insertElement( std::vector<unsigned int> Bundle );
	void updateLinearSystem();

	// DEBUGGING FUNCTIONS:
	void getInfo();

private:
	bool isEntryExist( unsigned int Index );
	bool isEntryExist( std::string Name );

	std::unordered_map<unsigned int, std::shared_ptr<Group>> m_HashTableByIndex;
	std::unordered_map<std::string, std::shared_ptr<Group>> m_HashTableByName;
	std::shared_ptr<const NodeList> m_Nodes;

	// Forbidden operation
	GroupList& operator=( const GroupList& aList ) { return *this; };
};

#endif /* GROUPLIST_H_ */
