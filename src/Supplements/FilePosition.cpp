/*
 * FilePosiotion.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: ravil
 */

#include "FilePosition.h"

FilePosition::FilePosition() {
	// TODO Auto-generated constructor stub

}


FilePosition::FilePosition(const FilePosition& aFilePosition) {
	m_StartPosition = aFilePosition.getStartPosition();
	m_EndPosition = aFilePosition.getEndPosition();
}


FilePosition& FilePosition::operator =(const FilePosition& aFilePosition) {
	m_StartPosition = aFilePosition.getStartPosition();
	m_EndPosition = aFilePosition.getEndPosition();
	return *this;
}


FilePosition::~FilePosition() {
	// TODO Auto-generated destructor stub
}


void FilePosition::setStartPosition(std::ios::pos_type Position) {
	m_StartPosition = Position;
}


void FilePosition::setEndPosition(std::ios::pos_type Position) {
	m_EndPosition = Position;
}


std::ios::pos_type FilePosition::getStartPosition() const {
	return m_StartPosition;
}


std::ios::pos_type FilePosition::getEndPosition() const {
	return m_EndPosition;
}
