/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** DFS_LAZY.h
** Implementation of a trivial lazy dynamic algorithm for dynamic transitive closure
** based on the DFS approach.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#ifndef _DFS_LAZY_H
#define _DFS_LAZY_H
#include <vector>
#include "TC.h"

class DFS_LAZY : public TC {
private:
	std::vector< std::vector<int> > adjacency_list;
	std::vector<bool> visited;
	void runDFS(int curNode);
	unsigned int count;
	int cols;
	
public:
	const char* get_name() {
		return "Lazy DFS";
	}
	
	virtual void init(int n);
	virtual void ins(int i, int j);
	virtual void del(int i, int j);
	virtual unsigned int query();
	
	DFS_LAZY() {
	}
	
	~DFS_LAZY() {
	}
};

#endif //_DFS_LAZY_H
