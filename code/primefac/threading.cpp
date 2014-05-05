#include "threading.hpp"

namespace primefac
{
	/* thread functions */
	void primefacThreadFunc(const PrimefacThread::Configuration& config)
	{
		static std::atomic_bool finished(false);
		static std::atomic_size_t searched(0);

		std::size_t bitsetSize = sizeof(std::size_t)*8;


		std::mt19937 gen;
		std::uniform_int_distribution<std::size_t> choiceDist(0, 1);
		std::uniform_real_distribution<double> acceptDist(0.0, 1.0);

		gen.seed(readSeed());

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
		size_t bStart = 0;

		// thread 0 needs to know the number of a, a1, etc values
		double searchSize = 0.0;
		if(config.threadId == 0) {
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
		}

		for(std::size_t a = n/2+config.threadId; a <= n; a += config.numThreads) {
			for(std::size_t a1 = 1; a1 <= a; a1++) {


				A.makeRandom(a, a1, gen);
				Anew = A;

				bStart = n-a;
				if(bStart <= 1) {
					bStart = 2;
				}

				for(std::size_t b = bStart; b <= n-a+1; b++) {
					for(std::size_t b1 = 1; b1 <= b; b1++) {
#ifndef PRIMEFAC_NO_PROGRESS
						if(config.threadId == 0) {
							std::cout << "Thread 0:\ta=" << a << " a1=" << a1 << " b=" << b << " b1=" << b1 << "\t" << (double)searched / searchSize << "%" << std::endl;
						}
#endif

						searched++;

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

	void semiprimeThreadFunc(const SemiprimeThread::Configuration& config)
	{
		static std::atomic_bool finished(false);
		static std::atomic_size_t searched(0);

		std::size_t bitsetSize = 8*sizeof(std::size_t);

		Bitset A(bitsetSize);
		Bitset B(bitsetSize);
		Bitset Anew(bitsetSize);
		Bitset Bnew(bitsetSize);
		Bitset prod(bitsetSize);
		std::mt19937 gen;
		std::uniform_int_distribution<std::size_t> choiceDist(0, 1);
		std::uniform_real_distribution<double> acceptDist(0.0, 1.0);

		gen.seed(readSeed());

		std::size_t N = config.prime1*config.prime2;
		Bitset Nbit(bitsetSize, N);
		Bitset N1bit(bitsetSize, config.prime1);
		Bitset N2bit(bitsetSize, config.prime2);
		std::size_t a = N1bit.getRelevant();
		std::size_t b = N2bit.getRelevant();
		std::size_t a1 = N1bit.numOnes();
		std::size_t b1 = N2bit.numOnes();
		std::size_t compliance = 0;
		std::size_t complianceNew = 0;
		double searchSize = (double)(config.numConfigurations*config.numAnnealingSteps*config.numThreads)/100.0;
	
		A.makeRandom(a, a1, gen);
		B.makeRandom(b, b1, gen);
		Anew = A;
		Bnew = B;

		Anew.multiply(Bnew, prod);
		compliance = prod.linearCompliance(Nbit);

		if(prod == Nbit) {
			std::cout << Anew.toSizeT() << " " << Bnew.toSizeT() << std::endl;
			finished = true;
			return;
		}

		double T = 1.0;

		for(std::size_t i = 0; i < config.numConfigurations; i++) {
#ifndef PRIMEFAC_NO_PROGRESS
			if(config.threadId == 0) {
				std::cout << (double)searched / searchSize << "%" << std::endl;
			}
#endif
			if(finished) {
				return;
			}
			for(std::size_t j = 0; j < config.numAnnealingSteps; j++) {
				if(choiceDist(gen)) {
					Anew.randomOperation(gen);
				} else {
					Bnew.randomOperation(gen);
				}

				Anew.multiply(Bnew, prod);
				if(prod == Nbit) {
					std::cout << Anew.toSizeT() << " " << Bnew.toSizeT() << std::endl;
					finished = true;
					return;
				}

				complianceNew = prod.quadraticCompliance(Nbit);
				if(complianceNew > compliance) {
					A = Anew;
					B = Bnew;
					compliance = complianceNew;
				} else if(acceptDist(gen) < exp(((double)(compliance-complianceNew))/(config.kB*T))) {
					A = Anew;
					B = Bnew;
					compliance = complianceNew;
				} else {
					Anew = A;
					Bnew = B;
				}

				searched++;
			}
			T *= config.coolingFactor;
		}
	}
	/* thread functions */


	/* PrimefacThread */
	std::atomic_bool PrimefacThread::completed(false);
	std::atomic_size_t PrimefacThread::numSearched(0);

	PrimefacThread::PrimefacThread(PrimefacThread::Configuration& config) : 
		thr(std::thread(primefacThreadFunc, config))
	{
	}

	void PrimefacThread::join()
	{
		thr.join();
	}

	std::vector<PrimefacThread::Configuration> PrimefacThread::createConfigurations(
			std::size_t number, std::size_t numConfigurations,
			std::size_t numAnnealingSteps, double coolingFactor, 
			double kB, std::size_t numThreads)
	{
		std::vector<Configuration> config;
		Configuration current;
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
	/* PrimefacThread */

	/* SemiprimeThread */
	std::atomic_bool SemiprimeThread::completed(false);
	std::atomic_size_t SemiprimeThread::numSearched(0);

	SemiprimeThread::SemiprimeThread(SemiprimeThread::Configuration& config) :
		thr(std::thread(semiprimeThreadFunc, config))
	{
	}

	void SemiprimeThread::join()
	{
		thr.join();
	}

	std::vector<SemiprimeThread::Configuration> SemiprimeThread::createConfigurations(
			std::size_t prime1, std::size_t prime2,
			std::size_t numConfigurations, std::size_t numAnnealingSteps,
			double coolingFactor, double kB, std::size_t numThreads)
	{
		std::vector<SemiprimeThread::Configuration> config;
		SemiprimeThread::Configuration current;
		current.prime1 = prime1;
		current.prime2 = prime2;
		current.numConfigurations = numConfigurations/numThreads;
		current.numAnnealingSteps = numAnnealingSteps;
		current.coolingFactor = coolingFactor;
		current.kB = kB;
		current.numThreads = numThreads;

		for(std::size_t i = 0; i < numThreads; i++) {
			current.threadId = i;
			config.push_back(current);
		}
		for(size_t i = 0; i < numConfigurations%numThreads; i++) {
			config[i].numConfigurations++;
		}
		return config;
	}
}
