/*
 * Group.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: ravil
 */

#include "Group.h"
#include <iostream>
#include <string>

#include "../Conditions/AbstractCondition.h"
#include "../Conditions/SHT_General.h"
#include "../Conditions/SHT_BC_FirstType.h"
#include "../Conditions/SHT_BC_SecondType.h"
#include "../Conditions/SHT_BC_ThirdType.h"


Group::Group() : m_Index(0),
				 m_Name("Unknown"),
				 m_Nodes( 0 ),
				 m_Condition(0) {

}


Group::Group(unsigned int Index,
			 std::string Name,
			 std::shared_ptr<const NodeList> Nodes )
									: m_Index(Index),
									  m_Name(Name),
									  m_Nodes( Nodes ),
									  m_Condition(0) {

}


Group::~Group() {
	// TODO Auto-generated destructor stub
}


void Group::setIndex(unsigned int Index) {
	m_Index = Index;
}


void Group::setName(std::string Name) {
	m_Name = Name;
}


unsigned int Group::getIndex() {
	return m_Index;
}


void Group::insertCondition( std::shared_ptr<AbstractCondition> Condition ) {
	if ( Condition.get() != 0 ) {
		m_Condition = Condition;
	}
	else {
		std::cout << "A condition has already be set" << std::endl;
	}
}


std::string Group::getName() {
	return m_Name;
}

unsigned int Group::getUpdatePriority() {
	return m_Condition->getUpdatePriority();
}

bool Group::isGroupReady() {
	if ( m_Condition.get() != 0 ) {
		return true;
	}
	return false;
}
