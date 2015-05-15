/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** TD_EAGER.cpp
** Implementation of a truly dynamic algorithm for dynamic transitive closure
** based on Shankowsis randomized reduction of dynamic transitive closure to dynamic matrix adjoint.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#include "TD_EAGER.h"
using namespace std;
void TD_EAGER::init(int n) {
	//initialize the adjacency matrix where we will store all the edges that are part of the graph
	//we need it in case our randomized algorithm fails (division by zero) to be able to reconstruct
	//the 
	if(adjacency_matrix != NULL) delete[] adjacency_matrix;
	this->n = n;
	adjacency_matrix = new uint32_t[n*n];
	memset(adjacency_matrix, 0, n*n*sizeof(uint32_t));
	//initialize the inverse matrix to be I-A, A is zero at first at the moment so I-A = I.
	inverse_matrix = new uint32_t[n*n];
	memset(inverse_matrix, 0, n*n*sizeof(uint32_t));
	for(int i=0;i<n;i++) {
        inverse_matrix[i*n + i] = 1;
        adjacency_matrix[i*n + i] = 1;
    }
	//initialize the counter to be n since all vertices can reach it self
	count = (uint32_t) n;

	xs = new uint32_t[n*n];
	for(int i = 0; i < n*n; i++) {
		xs[i] = next();
	}
}

void TD_EAGER::sherman_morrison(int i, int j, uint32_t u) {
	// We do not need v, since it is only a multiplication by 1
	//uint32_t v = 1;
	int k,m;
	//find (A^(-1)*u) => pick i-th column of A^(-1) and multiply every value by u
	uint32_t *a = new uint32_t[n];
	for(k=0;k<n;k++)
		a[k] = mod_mul(inverse_matrix[k*n+i],u);

	uint32_t *b = &inverse_matrix[j*n];

	//find 1 + v^T*A^(-1)*u - simply take the i'th entry and multiply by u
	uint32_t c = mod_add(1, mod_mul(u,b[i]));

	// Check that we do not divide by 0
	if(c == 0){
		// TODO: Use a better solutuon than simply exit!
		std::cout<<"Division by zero!!!!!!!!"<<std::endl;
		exit(1);
	}
	c = mod_inv(c);
	count = 0;
	// Be smart, do not multiply by 1
	if(c != 1) {
		//find the nominator of sherman morisson formula and divide with the denominator at the same time.
		uint32_t *e = new uint32_t[n*n];
		for(k=0;k<n;k++)
			for(m=0;m<n;m++)
				e[k*n+m] = mod_mul(c, mod_mul(a[k],b[m]));

		//update the inverse matrix and counter
		for(k=0;k<n;k++){
			for(m=0;m<n;m++){
				int index = k*n+m;
				inverse_matrix[index] = mod_sub(inverse_matrix[index], e[index]);
				if(inverse_matrix[index]!=0) count++;
			}
		}
		delete[] e;
	} else {
		// We do not need to multiply by 1
		// Calculate A^-1 - (fraction)
		for(k=0;k<n;k++){
			for(m=0;m<n;m++){
				int index = k*n+m;
				inverse_matrix[index] = mod_sub(inverse_matrix[index], mod_mul(a[k],b[m]));
				if(inverse_matrix[index]!=0) count++;
			}
		}
	}

	delete[] a;
}


void TD_EAGER::ins(int i, int j) {
	uint32_t u = xs[i*n + j];
	adjacency_matrix[i*n + j] = u;
	
	//update the inverse matrix
	sherman_morrison(i, j, u);
	
}

void TD_EAGER::del(int i, int j) {
	// This is the same as inserting -u = P - u in the Z_P field
	sherman_morrison(i, j, (uint32_t) (P-adjacency_matrix[i*n + j]));
	adjacency_matrix[i*n + j] = 0;
}

unsigned int TD_EAGER::query() {
	// Oh, we were eager, wasn't we?
	return count;
}
