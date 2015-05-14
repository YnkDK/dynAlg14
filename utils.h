/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** utils.cpp
** Helper functions to do arithmetic modulo operations in a finite field
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/
#ifndef UTILS
#define UTILS
#include <stdint.h> //< uint32_t uint64_t
#include <random>	//< Mersenne twister random number engine
#include <iostream>

#ifndef P
	#define P 2147483647UL    //!< 2^31 - 1 = 2147483647
#endif
#ifndef SEED
	#define SEED 42
#endif

static std::mt19937 mersenne_twister_ (SEED);
static std::uniform_int_distribution<uint32_t> distribution_(0, P - 1);

inline uint32_t next() {
	return distribution_(mersenne_twister_);
}

/**
 * It is assumed that a and b is strictly smaller than P in all functions below
 */
 
inline uint32_t field(const uint32_t a) {
	return (uint32_t) ((a >= P) ? a % P : a);
}

inline uint32_t mod_add(const uint64_t a, const uint64_t b) {
	const uint64_t res = a + b;
	return (uint32_t) ((res >= P) ? res - P : res);
}

inline uint32_t mod_sub(const int64_t a, const int64_t b) {
	const int64_t res = a -  b;
	return (uint32_t) ((res < 0) ? res + P : (uint32_t) res);
}

inline uint32_t mod_mul(const uint64_t a, const uint64_t b) {
	const uint64_t res = a*b;
	return (uint32_t) ((res >= P) ? res % P : res);
}

/**
 *	Inspired by http://rosettacode.org/wiki/Modular_inverse#C.2B.2B
 *	TODO: Might be optimized
 */
inline uint32_t mod_inv(const uint32_t n) {
    if(n == 1) {
        return 1;
    }
	int64_t a;
	a = n;
	int64_t b = P;
	
	int64_t t, q;
	int64_t x0 = 0, x1 = 1;
	while (a > 1) {
		q = a / b;
		
		t = b;
		b = a % b;
		a = t;
		t = x0;
		x0 = x1 - q * x0;
		x1 = t;

	}
	if (x1 < 0) x1 += P;
	return (uint32_t) x1;
}

inline void printMatrix(uint32_t *matrix, int n) {
    std::cout << "{";
	for(int i = 0; i < n; i++) {
        std::cout << "{";
		for(int j = 0; j < n-1; j++) {
			std::cout << matrix[i*n + j] << ",";
		}
		std::cout << matrix[i*n + n-1]<< "}";
        if(i < n-1) {
            std::cout << ",";
        }
	}
    std::cout << "}" << std::endl;
}

#endif