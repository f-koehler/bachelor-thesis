#include "config.hpp"
#include "sieve.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
using namespace primefac;

void usage();

int main(int argc, char** argv)
{
	size_t N = 10000000;
	string path("primelist.txt");
	vector<size_t> primes;

	for(int i = 1; i < argc; i++) {
		string tmp(argv[i]);

		if(tmp == string("-N")) {
			if(i == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			i++;
			stringstream(string(argv[i])) >> N;
		} else if(tmp == string("-o")) {
			if(i == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			i++;
			path = string(argv[i]);
		} else if(tmp == string("--help")) {
			usage();
			return EXIT_FAILURE;
		} else {
			cerr << "Unknown argument \"" << tmp << "\"!" << endl << endl;;
			usage();
			return EXIT_FAILURE;
		}
	}

	sieveOfEratosthenes(primes, N);

	ofstream out("primelist.txt");

	for(size_t i = 0; i < primes.size(); i++) {
		out << primes[i] << endl;
	}

	out.close();
	
	return EXIT_SUCCESS;
}

void usage()
{
	cout << "primelist - write a list of prime numbers to a file" << endl;
	cout << endl;
	cout << "Usage: " << endl;
	cout << "primelist [options]" << endl;
	cout << endl;
	cout << "Options: " << endl;
	cout << " --help     " << " show this message" << endl;
	cout << " -N [value] " << " limit for the sieve algorithm" << endl;
	cout << " -o [path]  " << " the file to write the primes to" << endl;
}
