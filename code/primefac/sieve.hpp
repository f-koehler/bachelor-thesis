#ifndef SIEVE_H_
#define SIEVE_H_

#include "config.hpp"
#include <vector>
#include <cmath>
#include <cstring>

namespace primefac
{
	void sieveOfEratosthenes(std::vector<std::size_t>& primes, std::size_t limit);
}

#endif
