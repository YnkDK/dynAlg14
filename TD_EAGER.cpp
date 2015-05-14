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
	//initialize the counter to be 0 since no edges are part of the transitive closure within a graph with 0
	//edges.
	count = 0;
}

void TD_EAGER::updateInverseMatrix(int i, int j, uint32_t u)
{
	uint32_t v = 1;
	int k,m;
	//find (A^(-1)*u) => pick i-th column of A^(-1) and multiply every value by u
	uint32_t *a = new uint32_t[n];
	for(k=0;k<n;k++)
		a[k] = mod_mul(inverse_matrix[k*n+i],u);
	
	//find (v^T*A^(-1)) => pick j-th row of A^(-1) and multiply every value by v
	uint32_t *b = new uint32_t[n];
	for(k=0;k<n;k++)
		b[k] = mod_mul(inverse_matrix[j*n+k],v);
	
	//find v^T*A^(-1)*u
	uint32_t c = 0;
	for(k=0;k<n;k++)
		c = mod_add(c, mod_mul(a[k],b[k]));
	
	//find the denominator of sherman morisson formula
	uint32_t d = mod_add(c,1);
	
	if(d == 0){
		std::cout<<"Division by zero!!!!!!!!"<<std::endl;
		exit(1);
	}
	
	//find the nominator of sherman morisson formula and divide with the denominator at the same time.
	uint32_t *e = new uint32_t[n*n];
	for(k=0;k<n;k++)
		for(m=0;m<n;m++)
			e[k*n+m] = mod_mul(mod_inv(d),mod_mul(a[k],b[m]));
	
	//update the inverse matrix and counter
	count = 0;
	for(k=0;k<n;k++){
		for(m=0;m<n;m++){
			int index = k*n+m;
			inverse_matrix[index] = mod_sub(inverse_matrix[index], e[index]);
			if(inverse_matrix[index]!=0) count++;
		}
	}
		
	delete[] a;
	delete[] b;
	delete[] e;

}


void TD_EAGER::ins(int i, int j) {
	uint32_t u = next();
	adjacency_matrix[i*n + j] = u;
	
	//update the inverse matrix
	
	uint32_t v = 1;
	int k,m;
	//find (A^(-1)*u) => pick i-th column of A^(-1) and multiply every value by u
	uint32_t *a = new uint32_t[n];
	for(k=0;k<n;k++)
		a[k] = mod_mul(inverse_matrix[k*n+i],u);
	
	//find (v^T*A^(-1)) => pick j-th row of A^(-1) and multiply every value by v
	uint32_t *b = new uint32_t[n];
	for(k=0;k<n;k++)
		b[k] = mod_mul(inverse_matrix[j*n+k],v);
	
	//find v^T*A^(-1)*u
	uint32_t c = 0;
	for(k=0;k<n;k++)
		c = mod_add(c, mod_mul(a[k],b[k]));
	
	//find the denominator of sherman morisson formula
	uint32_t d = mod_add(c,1);
	
	if(d == 0){
		std::cout<<"Division by zero!!!!!!!!"<<std::endl;
		exit(1);
	}
	
	//find the nominator of sherman morisson formula and divide with the denominator at the same time.
	uint32_t *e = new uint32_t[n*n];
	for(k=0;k<n;k++)
		for(m=0;m<n;m++)
			e[k*n+m] = mod_mul(mod_inv(d),mod_mul(a[k],b[m]));
	
	//update the inverse matrix and counter
	count = 0;
	for(k=0;k<n;k++){
		for(m=0;m<n;m++){
			int index = k*n+m;
			inverse_matrix[index] = mod_sub(inverse_matrix[index], e[index]);
			if(inverse_matrix[index]!=0) count++;
		}
	}
		
	delete[] a;
	delete[] b;
	delete[] e;
	/*cout << "INSERT" << endl;
	printMatrix(adjacency_matrix, n);
	printMatrix(inverse_matrix, n);
	cout << endl << endl;*/
}

void TD_EAGER::del(int i, int j) {
	//update inverse matrix
	
	uint32_t u = adjacency_matrix[i*n + j];
	adjacency_matrix[i*n + j] = 0;

	//update the inverse matrix
	
	uint32_t v = 1;
	int k,m;
	//find (A^(-1)*u) => pick i-th column of A^(-1) and multiply every value by u
	uint32_t *a = new uint32_t[n];
	for(k=0;k<n;k++)
		a[k] = mod_mul(inverse_matrix[k*n+i],u);
	
	//find (v^T*A^(-1)) => pick j-th row of A^(-1) and multiply every value by v
	uint32_t *b = new uint32_t[n];
	for(k=0;k<n;k++)
		b[k] = mod_mul(inverse_matrix[j*n+k],v);
	
	//find v^T*A^(-1)*u
	uint32_t c = 0;
	for(k=0;k<n;k++)
		c = mod_add(c, mod_mul(a[k],b[k]));
	
	//find the denominator of sherman morisson formula
	uint32_t d = mod_sub(1,c);
	
	if(d == 0){
		std::cout<<"Division by zero!!!!!!!!"<<std::endl;
		exit(1);
	}
	
	//find the nominator of sherman morisson formula and divide with the denominator at the same time.
	uint32_t *e = new uint32_t[n*n];
	for(k=0;k<n;k++)
		for(m=0;m<n;m++)
			e[k*n+m] = mod_mul(mod_inv(d),mod_mul(a[k],b[m]));
	
	//update the inverse matrix and counter
	count = 0;
	for(k=0;k<n;k++){
		for(m=0;m<n;m++){
			int index = k*n+m;
			inverse_matrix[index] = mod_add(inverse_matrix[index], e[index]);
			if(inverse_matrix[index]!=0) count++;
		}
	}
		
	delete[] a;
	delete[] b;
	delete[] e;
    /*cout << "DELETE" << endl;
    printMatrix(adjacency_matrix, n);
    printMatrix(inverse_matrix, n);
    cout << endl << endl;*/
}

unsigned int TD_EAGER::query() {
	return count;
}
