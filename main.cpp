/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** main.cpp
** Runs tests (correctness and execution time) for all implementations.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#include <iostream>
#include <stdio.h>

#include "TC.h"
#include "FW_LAZY.h"
#include "FW_EAGER.h"

#include "input_reader.h"

void print_matrix(bool *matrix, unsigned int n) {
	unsigned int i, j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			std::cout << matrix[i*n + j] << " ";
		}
		std::cout << std::endl;
	}
}

int main(int argc, const char* argv[]) {
	// First define which algorithms to run
	std::vector<TC*> algorithms = {
		new FW_LAZY(),
		new FW_EAGER()
	}; 
	// Then define input
	std::vector<Input> change_sequence;
	read_input("input/changefile3.txt", change_sequence);
	
	TC *tc = NULL;
	for(auto &alg : algorithms) {
		tc = alg;
		std::cout << "Running: " << alg->get_name() << std::endl;
		for (auto &change : change_sequence) {
			switch(change.type) {
			case 3:
				tc->init(change.i);
				break;
			case 2:
				std::cout << "Query: " << tc->query() << std::endl;
				break;
			case 1:
				tc->del(change.i, change.j);
				break;
			case 0:
				tc->ins(change.i, change.j);
				break;
			default:
				std::cout << "ERROR!!" << std::endl;
				return 1;
			}
		}
		std::cout << std::endl;
	}
	return 0;
}
