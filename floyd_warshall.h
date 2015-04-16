/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** floyd_warshall.h
** Implementation of the Floyd-Warshall transitive closure algorithm as
** described in the report - inspired by TRANSITIVE-CLOSURE(G) given in
** Cormen et. al. 3rd edition p. 698
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#ifndef _FLOYD_WARSHALL_H
#define _FLOYD_WARSHALL_H

unsigned int transitive_closure(bool *adjacency_matrix, unsigned int n);

#endif //_FLOYD_WARSHALL_H
