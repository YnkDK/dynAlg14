/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** utils.cpp
** Helper functions to do arithmetic modulo operations in a finite field
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/
#include <stdint.h> //< uint32_t uint64_t
#include <random>	//< Mersenne twister random number engine

#ifndef P
	#define P 2147483647ULL	//!< 2^31 - 1 = 2147483647
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
	return (a >= P) ? a % P : a;
}

inline uint32_t mod_add(const uint32_t a, const uint32_t b) {
	const uint64_t res = a + b;
	return (res >= P) ? res - P : P;
}

inline uint32_t mod_sub(const uint32_t a, const uint32_t b) {
	const int64_t res = a - b;
	return (res < 0) ? res + P : res;
}

inline uint32_t mod_mul(const uint32_t a, const uint32_t b) {
	const uint64_t res = a*b;
	return (res >= P) ? res % P : res;
}

/**
 *	Inspired by http://rosettacode.org/wiki/Modular_inverse#C.2B.2B
 *	TODO: Might be optimized
 */
inline uint32_t mod_inv(uint32_t a) {
	int32_t b = P;
	
	int32_t t, q;
	int32_t x0 = 0, x1 = 1;
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
	return x1;
}
