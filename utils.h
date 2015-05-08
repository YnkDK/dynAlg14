/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** utils.cpp
** Helper functions to do arithmetic modulo operations in a finite field
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/
#include <iostream> //< TODO: Remove this and main function
#include <cstdlib> //< div
#include <stdint.h> //< uint32_t uint64_t

/**
 * It is assumed that a and b is strictly smaller than P in all functions below
 */
 
#define P 2147483647ULL	//!< 2^31 - 1 = 2147483647

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

inline uint32_t mod_inv(const uint32_t a, const uint32_t p) {

}



int main() {
//	std::cout << mod_add(2147483645UL, 1231) << std::endl;
//	std::cout << (2147483645ULL+1231) % P << std::endl;
	
//	std::cout << mod_sub(1231, 2147483645UL) << std::endl;
//	std::cout << ((1231-2147483645UL)+P) % P << std::endl;
	
//	std::cout << mod_mul(2147483645UL, 2147483645UL) << std::endl;
//	std::cout << (2147483645UL * 2147483645UL) % P << std::endl;
	std::cout << mod_inv(123125) << " < " << P << std::endl;
}
