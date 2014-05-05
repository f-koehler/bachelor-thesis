#include "sieve.hpp"

namespace primefac
{
	void sieveOfEratosthenes(std::vector<std::size_t>& primes, std::size_t limit)
	{
		bool* cancel = new bool[limit+1];
		cancel[0] = true;
		cancel[1] = true;
		memset((void*)cancel, 0, (limit+1)*sizeof(bool));

		primes.clear();

		for(std::size_t i = 2; i <= limit; i++) {
			if(!cancel[i]) {
				for(std::size_t j = 2; i*j <= limit; j++) {
					cancel[i*j] = true;
				}
			}
		}

		for(std::size_t i = 2; i <= limit; i++) {
			if(!cancel[i]) {
				primes.push_back(i);
			}
		}
	}
}
