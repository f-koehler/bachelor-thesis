#include "bitset.hpp"
#include "seed.hpp"
#include <iostream>
#include <vector>
#include <cmath>
using namespace primefac;
using namespace std;

typedef struct {
	size_t a;
	size_t b;
	size_t a1;
	size_t b1;
} Step;

int main() {
	// Simulation parameters
	size_t N  = 100;
	size_t Na = 100;
	size_t Nc = 1500;
	double Fc = 0.997;
	double kB = 15.0;

	size_t size = sizeof(size_t)*8;

	// Bitsets
	Bitset Nbit(size, N);
	size_t n = Nbit.getRelevant();

	vector<Step> steps;
	Step step = {0, 0, 0, 0};
	size_t stepCount = 0;

	for(size_t a = n/2; a <= n; a++) {
		step.a = a;
		for(size_t b = n-a; b <= n-a+1; b++) {
			step.b = b;
			for(size_t a1 = 1; a1 <= a; a1++) {
				step.a1 = a1;
				for(size_t b1 = 1; b1 <= b; b1++) {
					step.b1 = b1;

					steps.push_back(step);
				}
			}
		}
	}
	stepCount = steps.size();

	size_t a_cur = 0;
	size_t b_cur = 0;
	size_t a1_cur = 0;
	size_t b1_cur = 0;

	double T = 1.0;
	size_t compliance = 0;
	size_t complianceNew = 0;
	size_t complianceTarget = Nbit.quadraticCompliance(Nbit);

	Bitset A(size);
	Bitset B(size);
	Bitset Anew(size);
	Bitset Bnew(size);
	Bitset prod(size, n);

	mt19937 gen;
	uniform_int_distribution<short> choiceDist(0, 1);
	uniform_real_distribution<double> acceptDist(0.0, 1.0);

	size_t prodNumber = 0;

	for(size_t i = 0; i < stepCount; i++) {
		cout << steps[i].a << " " << steps[i].b << endl;
		if(steps[i].a != a_cur) {
			a_cur = steps[i].a;
			A = Bitset(a_cur, true);
			Anew = A;
		}
		if(steps[i].b != b_cur) {
			b_cur = steps[i].b;
			B = Bitset(a_cur, true);
			Bnew = B;
		}
		if(steps[i].a1 != a1_cur) {
			a1_cur = steps[i].a1;
			A.makeRandom(a_cur, a1_cur, gen);
			Anew = A;
		}
		if(steps[i].b1 != b1_cur) {
			b1_cur = steps[i].b1;
			B.makeRandom(b_cur, b1_cur, gen);
			Anew = A;
		}

		prod = Bitset(size, A.toSizeT()*B.toSizeT());
		compliance = prod.quadraticCompliance(Nbit);

		if(compliance == complianceTarget) {
			cout << A.toSizeT() << " " << B.toSizeT() << endl;
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

				if(Nbit == prod) {
					cout << Nbit << " " << prod << endl;
					cout << A.toSizeT() << " " << B.toSizeT() << endl;
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

	return 0;
}
