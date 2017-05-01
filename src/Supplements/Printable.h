/*
 * Printable.h
 *
 *  Created on: Mar 29, 2017
 *      Author: ravil
 */

#include <iostream>
#include <fstream>
#include <string>

#ifndef PRINTABLE_H_
#define PRINTABLE_H_

class Printable {
public:
	Printable();
	virtual ~Printable();

	void print( std::string String,
				std::streambuf* OutputBuffer = std::cout.rdbuf() );

	static const std::string END_OF_STRING;
};

#endif /* PRINTABLE_H_ */
