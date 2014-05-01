#include "threading.hpp"

namespace primefac
{
	std::vector<PrimefacConfiguration> createPrimefacConfigurations(
			std::size_t number, std::size_t numConfigurations,
			std::size_t numAnnealingSteps, double coolingFactor, 
			double kB, std::size_t numThreads)
	{
		std::vector<PrimefacConfiguration> config;
		PrimefacConfiguration current;
		current.number = number;
		current.numConfigurations = numConfigurations;
		current.numAnnealingSteps = numAnnealingSteps;
		current.coolingFactor = coolingFactor;
		current.kB = kB;
		current.numThreads = numThreads;

		for(std::size_t i = 0; i < numThreads; i++) {
			current.threadId = i;
			config.push_back(current);
		}
		return config;
	}

	void primefacThreadFunc(const PrimefacConfiguration& config)
	{
		std::size_t bitsetSize = sizeof(std::size_t)*8;

		static std::atomic_bool finished(false);

		std::mt19937 gen;
		std::uniform_int_distribution<std::size_t> choiceDist(0, 1);
		std::uniform_real_distribution<double> acceptDist(0.0, 1.0);
		gen.seed(42);

		Bitset N(bitsetSize, config.number); 
		Bitset A(bitsetSize);
		Bitset B(bitsetSize);
		Bitset Anew(bitsetSize);
		Bitset Bnew(bitsetSize);
		Bitset prod(bitsetSize);

		std::size_t n = N.getRelevant();
		
		std::size_t compliance = 0;
		std::size_t newCompliance = 0;
		double T = 1.0;

		for(std::size_t a = n/2+config.threadId; a <= n; a += config.numThreads) {
			for(std::size_t a1 = 1; a1 <= a; a1++) {
				A.makeRandom(a, a1, gen);
				Anew = A;

				for(std::size_t b = n-a; b <= n-a+1; b++) {
					for(std::size_t b1 = 1; b1 <= b; b1++) {
						std::cout << "Thread " << config.threadId << ": "<< "a=" << a << " a1=" << a1 << " b=" << b1 << " b1=" << b1 << std::endl;

						B.makeRandom(b, b1, gen);
						Bnew = B;

						Anew.multiply(Bnew, prod);
						compliance = N.quadraticCompliance(prod);

						if(N == prod) {
							finished = true;
							std::cout << Anew << "\t" << Bnew << std::endl;
							std::cout << Anew.toSizeT() << "\t" << Bnew.toSizeT() << std::endl;
							return;
						}

						for(std::size_t i = 0; i < config.numAnnealingSteps; i++) {
							if(finished) {
								return;
							}
							for(std::size_t j = 0; j < config.numConfigurations; j++) {
								if(choiceDist(gen)) {
									Anew.randomOperation(gen);
								} else {
									Bnew.randomOperation(gen);
								}

								Anew.multiply(Bnew, prod);

								if(N == prod) {
									finished = true;
									std::cout << Anew << "\t" << Bnew << std::endl;
									std::cout << Anew.toSizeT() << "\t" << Bnew.toSizeT() << std::endl;
									return;
								}
								
								newCompliance = N.quadraticCompliance(prod);
								if(newCompliance > compliance) {
									A = Anew;
									B = Bnew;
								} else {
									if(acceptDist(gen) < exp(((double)(compliance-newCompliance))/(config.kB*T))) {
										A = Anew;
										B = Bnew;
									} else {
										Anew = A;
										Bnew = B;
									}
								}
							}							

							T *= config.coolingFactor;
						}
					}
				}
			}
		}
	}
}
