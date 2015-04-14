/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** FW.h
** Implementation of a trivial dynamic algorithm for dynamic transitive closure
** based on the Floyd-Warshall algorithm.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#ifndef _FW_H
#define _FW_H

#include "TC.h"

class FW : public TC {

public:
	const char* getName() {
		return "FW";
	}
	
	FW() {
		
	}
};

#endif //_FW_H
