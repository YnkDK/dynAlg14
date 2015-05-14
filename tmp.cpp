#include <iostream> //< TODO: Remove this and main function
#include "utils.h"

int main() {
//	std::cout << mod_add(2147483645UL, 1231) << std::endl;
//	std::cout << (2147483645ULL+1231) % P << std::endl;
	
//	std::cout << mod_sub(1231, 2147483645UL) << std::endl;
//	std::cout << ((1231-2147483645UL)+P) % P << std::endl;
	
//	std::cout << mod_mul(2147483645UL, 2147483645UL) << std::endl;
//	std::cout << (2147483645UL * 2147483645UL) % P << std::endl;
	std::cout << mod_inv(123125) << " < " << P << std::endl;
}
