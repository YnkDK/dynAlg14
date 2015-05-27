/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** FW_LAZY.h
** Implementation of a trivial dynamic algorithm for dynamic transitive closure
** based on the Floyd-Warshall algorithm.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#ifndef _FW_LAZY_H
#define _FW_LAZY_H

#include "TC.h"
#include "floyd_warshall.h"

class FW_LAZY : public TC {
private:
    bool *adjacency_matrix;
    unsigned int cols;

public:
    const char *get_name() {
        return " Lazy Floyd-Warshall";
    }

    virtual void init(int n);

    virtual void ins(int i, int j);

    virtual void del(int i, int j);

    virtual unsigned int query();

    FW_LAZY() {
        cols = -1;
        adjacency_matrix = NULL;
    }

    ~FW_LAZY() {
        if (adjacency_matrix != NULL) delete[] adjacency_matrix;
    }
};

#endif //_FW_LAZY_H
