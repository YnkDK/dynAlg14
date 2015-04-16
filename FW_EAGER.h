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
	
public:
	const char* get_name() {
		return "Eager Floyd-Warshall";
	}
	
	virtual void init(int n);
	virtual void ins(int i, int j);
	virtual void del(int i, int j);
	virtual unsigned int query();
	
	FW_EAGER() {
		cols = -1;
		count = -1;
		adjacency_matrix = NULL;
	}
	
	~FW_EAGER() {
		if(adjacency_matrix != NULL) delete adjacency_matrix;
	}
};

#endif //_FW_EAGER_H
