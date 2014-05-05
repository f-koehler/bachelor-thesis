#ifndef SIEVE_H_
#define SIEVE_H_

#include "config.hpp"
#include <vector>
#include <cmath>
#include <cstring>

namespace primefac
{
	/**
	 * Uses the sieve of Eratosthenes to generate a vector of prime numbers up to a limit.
	 * @param[out] primes The vector that will store all the primes smaller than limit.
	 * @param[in] limit The limit for the prime search.
	 */
	void sieveOfEratosthenes(std::vector<std::size_t>& primes, std::size_t limit);
}

#endif
