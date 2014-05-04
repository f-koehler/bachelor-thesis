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
		} else {
			cerr << "Unknown argument \"" << tmp << "\"!" << endl << endl;;
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

	// working variables
	Bitset Nbit(size, N);
	size_t n = Nbit.getRelevant();
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
	size_t bStart = 0;

	// count the a, a1, b, b1 values
	double searchSize = 0.0;
	for(size_t a = n/2; a <= n; a++) {
		for(size_t a1 = 1; a1 <= a; a1++) {

			bStart = n-a;
			if(bStart <= 1) {
				bStart = 2;
			}

			for(size_t b = bStart; b <= n-a+1; b++) {
				for(size_t b1 = 1; b1 <= n; b1++) {
					searchSize += 1.0;
				}
			}
		}
	}
	searchSize /= 100.0;


	// run
	for(size_t a = n/2; a <= n; a++) {
		for(size_t a1 = 1; a1 <= a; a1++) {

			A.makeRandom(a, a1, gen);
			Anew = A;

			bStart = n-a;
			if(bStart <= 1) {
				bStart = 2;
			}

			for(size_t b = bStart; b <= n-a+1; b++) {
				for(size_t b1 = 1; b1 <= b; b1++) {

					cout << "a=" << a << " a1=" << a1 << " b=" << b << " b1=" << b1 << ":\t" << numSearched/searchSize << "%" << endl;
					numSearched += 1.0;

					B.makeRandom(b, b1, gen);
					Bnew = B;

					Anew.multiply(Bnew, prod);
					compliance = prod.quadraticCompliance(Nbit);

					if(prod == Nbit) {
						cout << Anew.toSizeT() << " " << Bnew.toSizeT() << endl;
						return EXIT_SUCCESS;
					}

					T = 1.0;
					for(size_t j = 0; j < Na; j++) {
						for(size_t k = 0; k < Nc; k++) {
							// do a random op and check whether it improves compliance
							if(choiceDist(gen)) {
								Anew.randomOperation(gen);
							} else {
								Bnew.randomOperation(gen);
							}

							Anew.multiply(Bnew, prod);

							if(prod == Nbit) {
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
						}

						T *= Fc;
					}
				}
			}
		}
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
