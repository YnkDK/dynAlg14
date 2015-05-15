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
	cols = n;
	//count = n;
	adjacency_matrix = new bool[n*n];
	current = new bool[n*n];
	memset(adjacency_matrix, false, n*n*sizeof(bool));
	memset(current, false, n*n*sizeof(bool));
	for(int k=0;k<cols;k++) current[k*cols+k] = true;
}

void FW_EAGER::ins(int i, int j) {
	adjacency_matrix[i*cols + j] = true;
	//count = transitive_closure(adjacency_matrix, cols);
	//or the i-th row with the j-th 
	current[i*cols+j] = true;
	size_t k,m;
	for(k=0;k<cols;k++)
		current[i*cols+k] |= current[j*cols+k];
	
	//or everything that reaches i with the row of j
	for(k=0;k<cols;k++)
		if(current[k*cols+i])
			for(m=0;m<cols;m++)
				current[k*cols+m] |= current[i*cols+m];
	count=0;
	for(k=0;k<cols;k++)
		for(m=0;m<cols;m++)
			if(current[k*cols+m])
				count = count + 1;
}

void FW_EAGER::del(int i, int j) {
	adjacency_matrix[i*cols + j] = false;
	count = transitive_closure(adjacency_matrix, cols, current);
	
}

unsigned int FW_EAGER::query() {
	return count;
}
