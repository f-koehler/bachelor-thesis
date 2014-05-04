#include "config.hpp"
#include "bitset.hpp"
#include "seed.hpp"
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

	size_t size = sizeof(size_t)*8;	

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
		} else { 
			cerr << "Unknown argument \"" << tmp << "\"!" << endl << endl;;
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

	// working variables
	size_t N = N1*N2;
	Bitset Nbit(size, N);
	Bitset N1bit(size, N1);
	Bitset N2bit(size, N2);
	size_t n = Nbit.getRelevant();
	size_t a = N1bit.getRelevant();
	size_t b = N2bit.getRelevant();
	size_t a1 = N1bit.numOnes();
	size_t b1 = N2bit.numOnes();
	double T = 1.0;
	size_t compliance = 0;
	size_t complianceNew = 0;
	Bitset A(size);
	Bitset B(size);
	Bitset Anew(size);
	Bitset Bnew(size);
	Bitset prod(size);
	mt19937 gen;
	uniform_int_distribution<short> choiceDist(0, 1);
	uniform_real_distribution<double> acceptDist(0.0, 1.0);
	double numSearched = 0.0;
	double searchSize = (double)(Nc*Na)/100.0;

	// run
	numSearched += 1.0;

	A.makeRandom(a, a1,gen);
	Anew = A;
	B.makeRandom(b, b1, gen);
	Bnew = B;

	Anew.multiply(Bnew, prod);
	compliance = prod.quadraticCompliance(Nbit);

	if(prod == Nbit) {
		cout << Nbit << " " << prod << endl;
		cout << Anew.toSizeT() << " " << Bnew.toSizeT() << endl;
		return EXIT_SUCCESS;
	}

	T = 1.0;
	for(size_t j = 0; j < Na; j++) {
		cout << numSearched/searchSize << "%" << endl;
		for(size_t k = 0; k < Nc; k++) {
			// do a random op and check whether it improves compliance
			if(choiceDist(gen)) {
				Anew.randomOperation(gen);
			} else {
				Bnew.randomOperation(gen);
			}

			Anew.multiply(Bnew, prod);

			if(prod == Nbit) {
				cout << Nbit << " " << prod << endl;
				cout << Anew.toSizeT() << " " << Bnew.toSizeT() << endl;
				return EXIT_SUCCESS;
			}
			complianceNew = prod.quadraticCompliance(Nbit);
			if(complianceNew > compliance) {
				A = Anew;
				B = Bnew;
				compliance = complianceNew;
			} else {
				if(acceptDist(gen) < exp(((double)(compliance-complianceNew))/(kB*T))) {
					A = Anew;
					B = Bnew;
					compliance = complianceNew;
				} else {
					Anew = A;
					Bnew = B;
				}
			}

			numSearched += 1.0;
		}

		T *= Fc;
	}
	return 0;
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
