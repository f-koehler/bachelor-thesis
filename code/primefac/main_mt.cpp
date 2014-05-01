#include "bitset.hpp"
#include "seed.hpp"
#include "threading.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <sstream>
#include <string>
using namespace primefac;
using namespace std;

void usage();

int main(int argc, char** argv)
{
	// standard simulation parameters
	size_t N  = 100;
	size_t Na = 1000;
	size_t Nc = 1500;
	double Fc = 0.997;
	double kB = 15.0;

	size_t size = sizeof(size_t)*8;	

	// parse command line arguments
	for(int arg = 1; arg < argc; arg++) {
		string tmp(argv[arg]);

		if(tmp == string("-N")) {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> N;
		} else if(tmp == string("-k")) {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> kB;
		} else if(tmp == string("-Na")) {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> Na;
		} else if(tmp == string("-Nc")) {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> Nc;
		} else if(tmp == string("-Fc")) {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> Fc;
		} else if(tmp == string("--help")) {
			usage();
			return EXIT_FAILURE;
		}
	}

	// print the parameters of the simulation to be done
	cout << "Parameters:" << endl;
	cout << "N  = " << N  << endl;
	cout << "k  = " << kB << endl;
	cout << "Na = " << Na << endl;
	cout << "Nc = " << Nc << endl;
	cout << "Fc = " << Fc << endl;
	cout << endl;

	vector<PrimefacConfiguration> config = createPrimefacConfigurations(N, Nc, Na, Fc, kB, 8);

	vector<thread> threads;
	for(size_t i = 0; i < 8; i++) {
		threads.push_back(thread(primefacThreadFunc, config[i]));
	}
	for(size_t i = 0; i < 8; i++) {
		threads[i].join();
	}

	return 0;
}

void usage()
{
	cout << "primefac - factorize numbers using simulated annealing" << endl;
	cout << endl;
	cout << "Usage:" << endl;
	cout << "  primefac [options]" << endl;
	cout << endl;
	cout << "Options:" << endl;
	cout << "  --help\tPrint this message" << endl;
	cout << "  -N [value]\tThe number to factor, must be larger than 1 and smaller than " << ULONG_MAX << endl;
	cout << "  -k [value]\tValue for the Boltzmann constant" << endl;
	cout << "  -Na [value]\tNumber of annealing steps"  << endl;
	cout << "  -Nc [value]\tNumber of conifgurations per annealing step" << endl;
	cout << "  -Fc [value]\tCooling factor per annealing step" << endl;
}
