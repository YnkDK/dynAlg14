/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** input_reader.cpp
** Reads and formats the input in the format given in the project description
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#include "input_reader.h"
#include <iostream>

void read_input(const char* path, std::vector<Input> &output) {
	const std::string INIT("init");
	const std::string QUERY("transitive closure?");
	const std::string DELETE("delete");
	const std::string INSERT("insert");
	
	std::ifstream input(path);
	std::string line;
	unsigned int i, j;
	std::size_t delimiter;
	
	if(input) {
		while(getline(input, line)) {
			Input in;
			if (!line.compare(0, INIT.size(), INIT)) {
				i = atoi(line.substr(INIT.size()+1, line.size()-INIT.size()-2).c_str());
				in.type = 3;
				in.i = i;
				in.j = -1;
			} else if(!line.compare(0, QUERY.size(), QUERY)) {
				in.type = 2;
				in.i = -1;
				in.j = -1;
			} else if(!line.compare(0, DELETE.size(), DELETE)) {
				delimiter = line.find(",");
				i = atoi(line.substr(DELETE.size()+1, line.size()-delimiter-2).c_str());
				j = atoi(line.substr(delimiter+1, line.size()-DELETE.size()-delimiter-2).c_str());
				in.type = 1;
				in.i = i;
				in.j = j;
			} else if(!line.compare(0, INSERT.size(), INSERT)) {
				delimiter = line.find(",");
				i = atoi(line.substr(INSERT.size()+1, line.size()-delimiter-2).c_str());
				j = atoi(line.substr(delimiter+1, line.size()-INSERT.size()-delimiter-2).c_str());
				in.type = 0;
				in.i = i;
				in.j = j;
			} else {
				// Error in input!
				output.clear();
				input.close();
				return;
			}
			output.push_back(in);
		}
		input.close();
	}
}
