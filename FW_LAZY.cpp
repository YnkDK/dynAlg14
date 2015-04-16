/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** FW_LAZY.cpp
** Implementation of a trivial lazy dynamic algorithm for dynamic transitive
** closure based on the Floyd-Warshall algorithm.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#include "FW_LAZY.h"

void FW_LAZY::init(int n) {
	if(adjacency_matrix != NULL) delete adjacency_matrix;
	cols = n;
	
	adjacency_matrix = new bool[n*n];
	memset(adjacency_matrix, false, n*n*sizeof(bool));
}

void FW_LAZY::ins(int i, int j) {
	adjacency_matrix[i*cols + j] = true;
}

void FW_LAZY::del(int i, int j) {
	adjacency_matrix[i*cols + j] = false;
}

unsigned int FW_LAZY::query() {
	return transitive_closure(adjacency_matrix, cols);
}
