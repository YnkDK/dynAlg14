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
#include <stdint-gcc.h>
#include <iostream>

class TD_EAGER : public TC {
private:
	bool *adjacency_matrix; //this stores all the inserts/deletes that have happened
	uint32_t *inverse_matrix; //this stores the inverse that we want to maintain
	uint32_t *xs; // The random numbers
	uint32_t n; // Number of vertices
	uint32_t count; // Number of reachable vertices for all vertices

	/**
	 * Implementation of the Sherman-Morrison formula to maintain (A-ei*u*ej^T)^(-1)
	 * @param i Row index
	 * @param j Column index
	 * @param u The value to be used in the update
	 */
	void sherman_morrison(int i, int j, uint32_t u);
	
public:
	const char* get_name() {
		return "Eager Sankowski";
	}
	
	virtual void init(int n);
	virtual void ins(int i, int j);
	virtual void del(int i, int j);
	virtual unsigned int query();
	virtual void jump(bool *state);
	
	TD_EAGER() {
		adjacency_matrix = NULL;
		inverse_matrix = NULL;
		xs = NULL;
	}
	
	~TD_EAGER() {
		if(adjacency_matrix != NULL) delete[] adjacency_matrix;
		if(inverse_matrix != NULL) delete[] inverse_matrix;
		if(xs != NULL) delete[] xs;
	}
};

#endif //__EAGER_H
