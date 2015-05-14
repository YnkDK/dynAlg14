/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** TD_EAGER.h
** Implementation of a truly dynamic algorithm for dynamic transitive closure
** based on Shankowsis randomized reduction of dynamic transitive closure to dynamic matrix adjoint.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#ifndef _TD_EAGER_H
#define _TD_EAGER_H

#include "TC.h"
#include "utils.h"
#include <iostream>

class TD_EAGER : public TC {
private:
	uint32_t *adjacency_matrix; //this stores all the inserts/deletes that have happened
	uint32_t *inverse_matrix; //this stores the inverse that we want to maintain
	int n;
	uint32_t count;
	void updateInverseMatrix(int i, int j, uint32_t u);
	
public:
	const char* get_name() {
		return "Truly dynamic";
	}
	
	virtual void init(int n);
	virtual void ins(int i, int j);
	virtual void del(int i, int j);
	virtual unsigned int query();
	
	TD_EAGER() {
	}
	
	~TD_EAGER() {
		if(adjacency_matrix != NULL) delete[] adjacency_matrix;
	}
};

#endif //__EAGER_H
