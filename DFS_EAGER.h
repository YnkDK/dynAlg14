/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** DFS_EAGER.h
** Implementation of a trivial eager dynamic algorithm for dynamic transitive closure
** based on the DFS approach.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#ifndef _DFS_EAGER_H
#define _DFS_EAGER_H
#include <vector>
#include "TC.h"

class DFS_EAGER : public TC {
private:
	std::vector< std::vector<int> > adjacency_list;
	std::vector<bool> visited;
	void runDFS(int curNode);
	void transitive_closure();
	unsigned int count;
	int cols;
	
public:
	const char* get_name() {
		return "Eager DFS";
	}
	
	virtual void init(int n);
	virtual void ins(int i, int j);
	virtual void del(int i, int j);
	virtual unsigned int query();
	virtual void jump(bool *state);
	
	DFS_EAGER() {
	}
	
	~DFS_EAGER() {
	}
};

#endif //_DFS_EAGER_H
