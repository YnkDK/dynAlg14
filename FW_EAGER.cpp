/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** FW_EAGER.cpp
** Implementation of a trivial eager dynamic algorithm for dynamic transitive
** closure based on the Floyd-Warshall algorithm.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#include "FW_EAGER.h"

void FW_EAGER::init(int n) {
	if(adjacency_matrix != NULL) delete[] adjacency_matrix;
	cols = n;
	count = n;
	
	adjacency_matrix = new bool[n*n];
	memset(adjacency_matrix, false, n*n*sizeof(bool));
}

void FW_EAGER::ins(int i, int j) {
	adjacency_matrix[i*cols + j] = true;
	count = transitive_closure(adjacency_matrix, cols);
}

void FW_EAGER::del(int i, int j) {
	adjacency_matrix[i*cols + j] = false;
	count = transitive_closure(adjacency_matrix, cols);
}

unsigned int FW_EAGER::query() {
	return count;
}
