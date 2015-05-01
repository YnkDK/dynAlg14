#include <iostream>

#define P 2147483647ULL	//!< 2^31 - 1 = 2147483647

unsigned long mod_add(const unsigned long a, const unsigned long b) {
	const unsigned long res = a + b;
	return (res >= P) ? res - P : P;
}

unsigned long mod_sub(const long a, const long b) {
	const long long res = a - b;
	return (res < 0) ? res + P : res;
}

unsigned long mod_mul(const unsigned long long a, const unsigned long long b) {
	const unsigned long long res = a*b;
	return (res >= P) ? res % P : res;
}

int main() {
	std::cout << mod_add(2147483645UL, 1231) << std::endl;
	std::cout << (2147483645ULL+1231) % P << std::endl;
	
	std::cout << mod_sub(1231, 2147483645UL) << std::endl;
	std::cout << ((1231-2147483645UL)+P) % P << std::endl;
	
	std::cout << mod_mul(2147483645UL, 2147483645UL) << std::endl;
	std::cout << (2147483645UL * 2147483645UL) % P << std::endl;
}
