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

class TC { 
public:
	virtual const char* getName() = 0;
	virtual ~TC() {/* stuff */}
};
#endif //_TC_H
