/*
 * Mesh.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: ravil
 */
#include <iostream>
#include "GroupList.h"
#include "Group.h"
#include "GroupOfLines.h"
#include "GroupOfPoints.h"
#include "GroupOfTriangles.h"

GroupList::GroupList() : m_Nodes(0) {
	// TODO Auto-generated constructor stub

}


GroupList::GroupList(std::shared_ptr<NodeList> Nodes)
											   : m_Nodes( Nodes ) {
}



GroupList::~GroupList() {
	// TODO Auto-generated destructor stub
}


void GroupList::insertGroup( std::shared_ptr<Group> aGroup ) {

	if ( isEntryExist( aGroup->getIndex() ) == false ) {
		m_HashTableByIndex.insert( { aGroup->getIndex(),aGroup } );
		m_HashTableByName.insert( { aGroup->getName(), aGroup } );
	}
	else {
		int Error(1);
		throw Error;
	}

}


void GroupList::insertGroup( std::vector<std::string> Container ) {
	/* Container specification:
	 *
	 * Container[0]: type of the group: Dot, Line, Triangle - unsigned int
	 * Container[1]: group index - unsigned int
	 * Container[2]: the name of a group - std::string
	 *
	 * */

	// Check if the group has already been embedded
	std::string GroupName = Container[2];
	if ( isEntryExist( GroupName ) == false ) {

		// Create an appropriate group based on the type of a group
		/* Type specification:
		 *
		 * 15 - 1-node point
		 * 1 - 2-node line
		 * 2 - 3-node triangle
		 * */

		std::shared_ptr<Group> aGroup(0);
		unsigned int Index = std::stoi( Container[1] );
		unsigned int Type = std::stoi( Container[0] );


		// Create the appropriate group according the specification
		// or throw an error
		switch ( Type ) {
			case 15:
				aGroup.reset( new GroupOfPoints( Index, GroupName, m_Nodes ));
				break;

			case 1:
				aGroup.reset( new GroupOfLines( Index, GroupName, m_Nodes ));
				break;

			case 2:
				aGroup.reset( new GroupOfTriangles( Index, GroupName, m_Nodes ));
				break;

			default:
				int Error(1);
				throw Error;
		}

		m_HashTableByIndex.insert( { aGroup->getIndex(),aGroup } );
		m_HashTableByName.insert( { aGroup->getName(), aGroup } );
	}
	else {
		int Error(1);
		throw Error;
	}

}


void GroupList::deleteGroup( std::string Name ) {

	//auto Entry = m_HashTableByIndex.find( aGroup->getIndex() );
	auto Entry = m_HashTableByName.find( Name );

	if ( Entry != m_HashTableByName.end() ) {
		m_HashTableByName.erase( Name );
		m_HashTableByIndex.erase( Entry->second->getIndex() );

	}
	else {
		int Error(1);
		throw Error;
	}
}


void GroupList::deleteGroup( unsigned int Index ) {

	auto Entry = m_HashTableByIndex.find( Index );

	if ( Entry != m_HashTableByIndex.end() ) {
		m_HashTableByIndex.erase( Index );
		m_HashTableByName.erase( Entry->second->getName() );
	}
	else {
		int Error(1);
		throw Error;
	}
}


void GroupList::insertCondition(std::string Name,
								std::shared_ptr<AbstractCondition> Condition) {

	if ( isEntryExist( Name ) ) {
		auto Entry = m_HashTableByName.find( Name );
		Entry->second->insertCondition( Condition );
	}
	else {
		int Error(1);
		throw Error;
	}

}



void GroupList::insertElement( std::vector<unsigned int> Bundle ) {
	// We assume that the file has never made mistakes
	// numbering Group Index in Bundles

	// It allows us to speed up the process of searching right groups
	// in the Hash Table ( there is no need in if-statements )

	auto Entry = m_HashTableByIndex.find( Bundle[3] );
	Entry->second->insertElement( Bundle );
}


unsigned int GroupList::getNumberOfGroups() {
	return m_HashTableByIndex.size();
}


void GroupList::printGroupsInfo() {

	unsigned int Counter = 0;
	for( auto Iterator = m_HashTableByIndex.begin();
		 Iterator != m_HashTableByIndex.end();
		 ++Iterator, ++Counter ) {

			std::cout << "********************" << std::endl;
			std::cout << "Entry number: " << Counter << std::endl;
			Iterator->second->getInfo();
			std::cout << "********************" << std::endl;
			std::cout << std::endl;
	}
}



bool GroupList::isEntryExist( unsigned int Index ) {
	bool Flag = true;

	if ( m_HashTableByIndex.find( Index ) == m_HashTableByIndex.end() ) {
		Flag = false;
	}

	return Flag;
}


unsigned int GroupList::getTotalNumberOfElements() {
	unsigned int TotalNumberOfElements(0);

	for ( auto Iterator = m_HashTableByIndex.begin();
			Iterator != m_HashTableByIndex.end();
			++Iterator ) {
		TotalNumberOfElements += Iterator->second->getNumberOfElements();
	}

	return TotalNumberOfElements;
}


unsigned int GroupList::getTotalNumberOfEntries() {
	unsigned int TotalNumberOfEntries(0);

	for ( auto Iterator = m_HashTableByIndex.begin();
			Iterator != m_HashTableByIndex.end();
			++Iterator ) {
		TotalNumberOfEntries += Iterator->second->getNumberOfEntriesInVtkTable();
	}

	return TotalNumberOfEntries;
}


void GroupList::printElementsAccordingToVtkFormat
										( std::streambuf* OutputBuffer ) {

	for ( auto Iterator = m_HashTableByIndex.begin();
			Iterator != m_HashTableByIndex.end();
			++Iterator ) {
		Iterator->second->printElementsAccordingToVtkFormat( OutputBuffer );
	}

	// Pint an empty string
	print( "", OutputBuffer);
}


void GroupList::printElementsTypeAccordingToVtkFormat
										( std::streambuf* OutputBuffer ) {
	for ( auto Iterator = m_HashTableByIndex.begin();
			Iterator != m_HashTableByIndex.end();
			++Iterator ) {
		Iterator->second->printElementsTypeAccordingToVtkFormat( OutputBuffer );
	}

	// Pint an empty string
	print( "", OutputBuffer);
}


bool GroupList::isEntryExist(std::string Name) {

	bool Flag = true;

	if ( m_HashTableByName.find( Name ) == m_HashTableByName.end() ) {
		Flag = false;
	}

	return Flag;

}


void GroupList::getInfo() {
	for ( auto Iterator = m_HashTableByIndex.begin();
			Iterator != m_HashTableByIndex.end();
			++Iterator ) {

		// ask all groups to print out their
		// boundaries information
		Iterator->second->getInfo();
	}
}


bool comparisonOfGroups( std::shared_ptr<Group> FirstGroup,
						 std::shared_ptr<Group> SecondGroup) {

	if ( SecondGroup->getUpdatePriority() > FirstGroup->getUpdatePriority() )
		return true;
	else
		return false;

}


void GroupList::updateLinearSystem() {

	// Create the update queue and fill it in with
	// all entries within the Hash table

	// Additionally the loop has to check
	// whether all groups are ready to update
	// if not then throw an error
	std::vector<std::shared_ptr<Group>> UpdateQueue;
	for( auto Iterator = m_HashTableByIndex.begin();
			Iterator != m_HashTableByIndex.end();
			++Iterator ) {


		if ( Iterator->second->isGroupReady() == false ) {
			int Error(1);
			throw Error;
		}


		UpdateQueue.push_back( Iterator->second );
	}


	// Sort all group in descending order according
	// their update priority coefficient
	std::sort(UpdateQueue.begin(),UpdateQueue.end(), comparisonOfGroups );


	// Update all groups in the descending order
	for( auto Iterator = UpdateQueue.begin();
				Iterator != UpdateQueue.end();
				++Iterator ) {
		Iterator->get()->updateLinearSystem();
		}
}


