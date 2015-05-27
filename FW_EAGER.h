/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** FW_EAGER.h
** Implementation of a trivial eager dynamic algorithm for dynamic transitive closure
** based on the Floyd-Warshall algorithm.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#ifndef _FW_EAGER_H
#define _FW_EAGER_H

#include "TC.h"
#include "floyd_warshall.h"

class FW_EAGER : public TC {
private:
	bool *adjacency_matrix;
	unsigned int cols;
	unsigned int count;
	bool *current;
	
public:
	const char* get_name() {
		return "Eager Floyd-Warshall";
	}
	
	virtual void init(int n);
	virtual void ins(int i, int j);
	virtual void del(int i, int j);
	virtual unsigned int query();
	void jump(bool *state);
	
	FW_EAGER() {
		cols = 0;
		count = 0;
		adjacency_matrix = NULL;
		current = NULL;
	}
	
	~FW_EAGER() {
		if(adjacency_matrix != NULL) delete[] adjacency_matrix;
		if(current != NULL) delete[] current;
	}
};

#endif //_FW_EAGER_H
