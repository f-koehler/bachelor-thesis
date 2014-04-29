#include "bitset.hpp"
#include "seed.hpp"
#include <iostream>
#include <vector>
#include <cmath>
using namespace primefac;
using namespace std;

int main() {
	// Simulation parameters
	size_t N  = 99999989237606677;;
	size_t Na = 250;
	size_t Nc = 1450000;
	double Fc = 0.997;
	double kB = 63365;
	size_t a = 29;
	size_t b = 29;
	size_t a1 = 12;
	size_t b1 = 16;

	size_t size = 59;

	// Bitsets
	Bitset Nbit(size, N);
	size_t n = Nbit.getRelevant();

	double T = 1.0;
	size_t compliance = 0;
	size_t complianceNew = 0;

	mt19937 gen;
	uniform_int_distribution<short> choiceDist(0, 1);
	uniform_real_distribution<double> acceptDist(0.0, 1.0);

	Bitset A(size, a, a1, gen);
	Bitset B(size, b, b1, gen);
	Bitset Anew(A);
	Bitset Bnew(B);
	Bitset prod(size, n);

	Anew.multiply(Bnew, prod);
	if(prod == Nbit) {
		cout << Nbit << " " << prod << endl;
		cout << A.toSizeT() << " " << B.toSizeT() << endl;
		return EXIT_SUCCESS;
	}
	T = 1.0;

	for(size_t i = 0; i < Na; i++) {
		cout << (double)i/(double)Na << "%" << endl;
		for(size_t j = 0; j < Nc; j++) {
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

	return 0;
}

