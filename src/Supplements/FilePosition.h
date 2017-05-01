/*
 * FilePosiotion.h
 *
 *  Created on: Mar 28, 2017
 *      Author: ravil
 */

#include <fstream>

#ifndef FILEPOSIOTION_H_
#define FILEPOSIOTION_H_

class FilePosition {
public:
	FilePosition();
	FilePosition( const FilePosition& );
	FilePosition& operator=( const FilePosition& );

	virtual ~FilePosition();

	void setStartPosition( std::ios::pos_type Position );
	void setEndPosition( std::ios::pos_type Position );

	std::ios::pos_type getStartPosition() const;
	std::ios::pos_type getEndPosition() const;

private:
	std::ios::pos_type m_StartPosition;
	std::ios::pos_type m_EndPosition;
};

#endif /* FILEPOSIOTION_H_ */
