/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** input_reader.h
** Reads and formats the input in the format given in the project description
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#ifndef _INPUT_READER_H
#define _INPUT_READER_H

#include <vector>
#include <fstream>
#include <string>

struct Input {
	int type; //< 0 = ins, 1 = del, 2 = query, 3 = init
	unsigned int i; //< Used if type is 0 or 1 - or equals n if type is 3
	unsigned int j; //< Used if type is 0 or 1
	bool *state;
};

void read_input(const char* path, std::vector<Input> &output);

#endif
