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
#include <iostream>
using namespace std;
void FW_EAGER::init(int n) {
	if(adjacency_matrix != NULL) delete[] adjacency_matrix;
	if(current != NULL) delete[] current;
	cols = n;
	//count = n;
	adjacency_matrix = new bool[n*n];
	current = new bool[n*n];
	memset(adjacency_matrix, false, n*n*sizeof(bool));
	memset(current, false, n*n*sizeof(bool));
	for(size_t k=0;k<cols;k++) current[k*cols+k] = true;
}

void FW_EAGER::ins(int i, int j) {
	adjacency_matrix[i*cols + j] = true;
	//count = transitive_closure(adjacency_matrix, cols);
	//or the i-th row with the j-th
	bool *tmp1, *tmp2;
	tmp1 = &current[i*cols];
	tmp2 = &current[j*cols];
	tmp1[j] = true;
	size_t k,m;
	for(k = 0; k < cols; ++k)
		tmp1[k] |= tmp2[k];
	
	//or everything that reaches i with the row of j
	tmp2 = &current[i*cols];
	for(k = 0; k < cols; ++k) {
		tmp1 = &current[k*cols];
		if(tmp1[i])
			for(m = 0; m < cols; ++m)
				tmp1[m] |= tmp2[m];
	}
	count=0;
	for(k=0;k<cols;k++) {
		tmp1 = &current[k*cols];
		for(m = 0; m < cols; ++m)
			if(tmp1[m])
				count = count + 1;
	}
}

void FW_EAGER::del(int i, int j) {
	adjacency_matrix[i*cols + j] = false;
	count = transitive_closure(adjacency_matrix, cols, current);
	
}

unsigned int FW_EAGER::query() {
	return count;
}
