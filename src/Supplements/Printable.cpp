/*
 * Printable.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: ravil
 */

#include "Printable.h"

const std::string Printable::END_OF_STRING("\n");

Printable::Printable() {
	// TODO Auto-generated constructor stub

}

Printable::~Printable() {
	// TODO Auto-generated destructor stub
}

void Printable::print(std::string String, std::streambuf* OutputBuffer) {
	std::string Line = String + END_OF_STRING;
	OutputBuffer->sputn(Line.c_str(),Line.size());
}
