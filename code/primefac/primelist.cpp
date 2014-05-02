#include "sieve.hpp"
#include <fstream>
using namespace std;
using namespace primefac;

int main()
{
	size_t N = 10000000;
	vector<size_t> primes;

	sieveOfEratosthenes(primes, N);

	ofstream out("primelist.txt");

	for(size_t i = 0; i < primes.size(); i++) {
		out << primes[i] << endl;
	}

	out.close();
	
	return EXIT_SUCCESS;
}
