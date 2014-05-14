#include "threading.hpp"

namespace primefac
{
	/* thread functions */
	void PrimefacThread::threadFunc(const Configuration& config)
	{
		std::size_t bitsetSize = sizeof(std::size_t)*8;

		Prng gen;
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
		size_t aStart = 0;
		factors.first = 0;
		factors.second = 0;

#ifdef PRIMEFAC_PROGRESS
		size_t searchSize = 0;
		if(config.threadId == 0) {
			aStart = n/2;
			if(n/2 == 1) {
				aStart = 2;
			}
			for(size_t a = n/2; a <= n; a++) {
				for(size_t a1 = 1; a1 <= a; a1++) {

					bStart = n-a;
					if(bStart <= 1) {
						bStart = 2;
					}

					for(size_t b = bStart; b <= n-a+1; b++) {
						for(size_t b1 = 1; b1 <= n; b1++) {
							searchSize++;
						}
					}
				}
			}
		}
#endif

		aStart = n/2;
		if(n/2 == 1) {
			aStart = 2;
		}
		for(std::size_t a = aStart+config.threadId; a <= n; a += config.numThreads) {
			for(std::size_t a1 = 1; a1 <= a; a1++) {


				A.makeRandom(a, a1, gen);
				Anew = A;

				bStart = n-a;
				if(bStart <= 1) {
					bStart = 2;
				}

				for(std::size_t b = bStart; b <= n-a+1; b++) {
					for(std::size_t b1 = 1; b1 <= b; b1++) {
#ifdef PRIMEFAC_PROGRESS
						if(config.threadId == 0) {
							std::cout << "Completion: " << ((double)numSearched)/((double)searchSize)*100.0 << "%" << std::endl;
						}
#endif
						B.makeRandom(b, b1, gen);
						Bnew = B;

						Anew.multiply(Bnew, prod);
						compliance = N.quadraticCompliance(prod);

						if(N == prod) {
							resultMutex.lock();
							if((factors.first == 0) || (factors.second == 0)) {
								completed = true;
								success = true;
								factors.first = Anew.toSizeT();
								factors.second = Bnew.toSizeT();
							}
							resultMutex.unlock();
							return;
						}

						for(std::size_t i = 0; i < config.numAnnealingSteps; i++) {
							if(completed) {
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
									resultMutex.lock();
									if((factors.first == 0) || (factors.second == 0)) {
										completed = true;
										success = true;
										factors.first = Anew.toSizeT();
										factors.second = Bnew.toSizeT();
									}
									resultMutex.unlock();
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
#ifdef PRIMEFAC_PROGRESS
						numSearched++;
#endif
					}
				}
			}
		}
	}

	void SemiprimeThread::threadFunc(const SemiprimeThread::Configuration& config)
	{
		std::size_t bitsetSize = 8*sizeof(std::size_t);

		Bitset A(bitsetSize);
		Bitset B(bitsetSize);
		Bitset Anew(bitsetSize);
		Bitset Bnew(bitsetSize);
		Bitset prod(bitsetSize);
		Prng gen;
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

#ifdef PRIMEFAC_PROGRESS
		std::size_t searchSize = config.numConfigurations*config.numAnnealingSteps*config.numThreads;
		std::size_t updateTarget = (std::size_t)(((double)(config.numConfigurations*config.numAnnealingSteps))*0.05);
		std::size_t updateCounter = 0;
#endif
	
		A.makeRandom(a, a1, gen);
		B.makeRandom(b, b1, gen);
		Anew = A;
		Bnew = B;

		Anew.multiply(Bnew, prod);
		compliance = prod.linearCompliance(Nbit);

		if(prod == Nbit) {
			resultMutex.lock();
			if(!success) {
				success = true;
				factors.first = Anew.toSizeT();
				factors.second = Bnew.toSizeT();
				completed = true;
			}
			resultMutex.unlock();
			return;
		}

		double T = 1.0;

		for(std::size_t i = 0; i < config.numConfigurations; i++) {
#ifdef PRIMEFAC_PROGRESS
			if((config.threadId == 0) && (updateCounter >= updateTarget)) {
				std::cout << "Completion: " << ((double)numSearched)/((double)searchSize)*100.0 << "%" << std::endl;
				updateCounter = 0;
			}
#endif
			if(completed) {
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
					resultMutex.lock();
					if(!success) {
						success = true;
						factors.first = Anew.toSizeT();
						factors.second = Bnew.toSizeT();
						completed = true;
					}
					resultMutex.unlock();
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

#ifdef PRIMEFAC_PROGRESS
				numSearched++;
				updateCounter++;
#endif
			}
			T *= config.coolingFactor;
		}
	}
	/* thread functions */


	/* PrimefacThread */
	std::atomic_bool PrimefacThread::completed(false);
#ifdef PRIMEFAC_PROGRESS
	std::atomic_size_t PrimefacThread::numSearched(0);
#endif

	std::mutex PrimefacThread::resultMutex;
	bool PrimefacThread::success(true);
	std::pair<std::size_t, std::size_t> PrimefacThread::factors;

	PrimefacThread::PrimefacThread(const PrimefacThread::Configuration& config) : 
		thr(std::thread(&PrimefacThread::threadFunc, this, config))
	{
	}

	void PrimefacThread::join()
	{
		thr.join();
	}
	
	bool PrimefacThread::getSuccess()
	{
		return success;
	}
	std::pair<std::size_t, std::size_t> PrimefacThread::getFactors()
	{
		return factors;
	}
	void PrimefacThread::reset()
	{
		success = false;
		factors.first = 0;
		factors.second = 0;
		completed = false;
#ifdef PRIMEFAC_PROGRESS
		numSearched = 0;
#endif
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
	std::mutex SemiprimeThread::resultMutex;
	std::atomic_bool SemiprimeThread::completed(false);
#ifdef PRIMEFAC_PROGRESS
	std::atomic_size_t SemiprimeThread::numSearched(0);
#endif
	bool SemiprimeThread::success(false);
	std::pair<std::size_t, std::size_t> SemiprimeThread::factors;

	SemiprimeThread::SemiprimeThread(const SemiprimeThread::Configuration& config) :
		thr(std::thread(&SemiprimeThread::threadFunc, this, config))
	{
	}

	void SemiprimeThread::join()
	{
		thr.join();
	}
		
	bool SemiprimeThread::getSuccess()
	{
		return success;
	}
	std::pair<std::size_t, std::size_t> SemiprimeThread::getFactors()
	{
		return factors;
	}
	void SemiprimeThread::reset()
	{
		success = false;
		factors.first = 0;
		factors.second = 0;
		completed = false;
#ifdef PRIMEFAC_PROGRESS
		numSearched = 0;
#endif
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
