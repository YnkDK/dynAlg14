/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** TC.h
** Interface used for all transitive closure algorithms implemeted.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/
#ifndef _TC_H
#define _TC_H

#include <string.h> //< memset, memcpy

class TC { 
public:
	virtual const char* get_name() = 0;
	virtual void init(int n) = 0;
	virtual void ins(int i, int j) = 0;
	virtual void del(int i, int j) = 0;
	virtual unsigned int query() = 0;
	virtual ~TC() {/* stuff */}
};
#endif //_TC_H
