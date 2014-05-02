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
	size_t N1 = 71;
	size_t N2 = 73;
	size_t Na = 1000;
	size_t Nc = 1500;
	double Fc = 0.997;
	double kB = 15.0;
	size_t numThreads = 8;

	// parse command line arguments
	for(int arg = 1; arg < argc; arg++) {
		string tmp(argv[arg]);

		if(tmp == string("-N1")) {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> N1;
		} else if(tmp == string("-N2")) {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> N2;
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
	cout << "N1 = " << N1 << endl;
	cout << "N2 = " << N2 << endl;
	cout << "N  = " << N1*N2 << endl;
	cout << "k  = " << kB << endl;
	cout << "Na = " << Na << endl;
	cout << "Nc = " << Nc << endl;
	cout << "Fc = " << Fc << endl;
	cout << endl;

	vector<SemiprimeConfiguration> config = createSemiprimeConfigurations(N1, N2, Nc, Na, Fc, kB, numThreads);
	vector<thread> threads;
	for(vector<SemiprimeConfiguration>::iterator i = config.begin(); i != config.end(); i++) {
		threads.push_back(thread(semiprimeThreadFunc, *i));
	}
	for(vector<thread>::iterator i = threads.begin(); i != threads.end(); i++) {
		i->join();
	}
}

void usage()
{
	cout << "semiprime - factorize semiprime numbers using simulated annealing" << endl;
	cout << endl;
	cout << "Usage:" << endl;
	cout << "  primefac [options]" << endl;
	cout << endl;
	cout << "Options:" << endl;
	cout << "  --help\tPrint this message" << endl;
	cout << "  -N1 [value]\tThe number to factor, must be larger than 1 and smaller than " << ULONG_MAX << endl;
	cout << "  -N2 [value]\tThe number to factor, must be larger than 1 and smaller than " << ULONG_MAX << endl;
	cout << "  -k [value]\tValue for the Boltzmann constant" << endl;
	cout << "  -Na [value]\tNumber of annealing steps"  << endl;
	cout << "  -Nc [value]\tNumber of conifgurations per annealing step" << endl;
	cout << "  -Fc [value]\tCooling factor per annealing step" << endl;
}
