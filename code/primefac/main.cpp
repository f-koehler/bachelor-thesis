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
	// Simulation parameters
	size_t N  = 100;
	size_t Na = 1000;
	size_t Nc = 1500;
	double Fc = 0.997;
	double kB = 15.0;

	size_t size = sizeof(size_t)*8;

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
		}
	}

	for(size_t a = n/2; a <= n; a++) {
		for(size_t a1 = 1; a1 <= a; a1++) {

			A.makeRandom(a, a1, gen);
			Anew = A;

			for(size_t b = n-a; b <= n-a+1; b++) {
				for(size_t b1 = 1; b1 <= b; b1++) {

					cout << "a=" << a << " a1=" << a1 << " b= " << b1 << " b1=" << b1 << endl;

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
	cout << "  -N [value]\tThe number to factor, must be larger than 1 and smaller than " << ULONG_MAX << endl;
	cout << "  -k [value]\tValue for the Boltzmann constant" << endl;
	cout << "  -Na [value]\tNumber of annealing steps"  << endl;
	cout << "  -Nc [value]\tNumber of conifgurations per annealing step" << endl;
	cout << "  -Fc [value]\tCooling factor per annealing step" << endl;
}
