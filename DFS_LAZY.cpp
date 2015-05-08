/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** DFS_LAZY.cpp
** Implementation of a trivial lazy dynamic algorithm for dynamic transitive closure
** based on the DFS approach.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#include "DFS_LAZY.h"
#include <iostream>
using namespace std;
void DFS_LAZY::init(int n) {
	if(adjacency_list.size() != 0) adjacency_list.clear();
	adjacency_list.resize(n); //allocate memory for the nodes
	visited.resize(n);
	cols = n;
	count = 0;
}

void DFS_LAZY::ins(int i, int j) {
	adjacency_list[i].push_back(j);
}

void DFS_LAZY::del(int i, int j) {
	//O(n) time deletion
	size_t k;
	for(k=0;k<adjacency_list[i].size();k++){
		if(adjacency_list[i][k] == j){
			adjacency_list[i].erase(adjacency_list[i].begin() + k);
			break;
		}
	}
}

void DFS_LAZY::runDFS(int curNode){
	count++;
	visited[curNode] = true;
	size_t i;
	for(i=0;i<adjacency_list[curNode].size();i++)
		if(!visited[adjacency_list[curNode][i]])
			runDFS(adjacency_list[curNode][i]);
}

unsigned int DFS_LAZY::query() {
	int i;
	count = 0;
	for(i=0;i<cols;i++){
		for(int j = 0; j < cols; j++) visited[j] = false;
		runDFS(i);
	}
	return count;
}

