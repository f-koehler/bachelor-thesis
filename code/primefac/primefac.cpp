#include "primefac.hpp"

namespace primefac
{
	PrimefacResult factorize(const PrimefacParameters& parameters)
	{
		PrimefacResult result;
		std::chrono::high_resolution_clock clock;
		std::chrono::high_resolution_clock::time_point start = clock.now();

		std::size_t size = sizeof(std::size_t)*8;
		Bitset Nbit(size, parameters.N);
		Bitset A(size);
		Bitset B(size);
		Bitset Anew(size);
		Bitset Bnew(size);
		Bitset prod(size);
		Prng gen(size);
		std::uniform_int_distribution<short> choiceDist(0, 1);
		std::uniform_real_distribution<double> acceptDist(0.0, 1.0);
		std::size_t n = Nbit.getRelevant();
		std::size_t aStart = 0;
		std::size_t bStart = 0;
		std::size_t compliance = 0;
		std::size_t complianceNew = 0;
		std::size_t usedSteps = 0;
		double T = 1.0;

#ifdef PRIMEFAC_PROGRESS
		std::size_t searchSize = 0;
		std::size_t numSearched = 0;

		aStart = n/2;
		if(aStart <= 1) {
			aStart = 2;
		}
		for(std::size_t a = aStart; a <= n; a++) {
			for(std::size_t a1 = 1; a1 <= a; a1++) {
				bStart = n-a;
				if(bStart <= 1) {
					bStart = 2;
				}
				for(std::size_t b = bStart; b <= n-a+1; b++) {
					for(std::size_t b1 = 1; b1 <= b; b1++) {
						searchSize++;
					}
				}
			}
		}
#endif

		result.success = false;

		aStart = n/2;
		if(aStart <= 1) {
			aStart = 2;
		}
		for(std::size_t a = aStart; a <= n; a++) {
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
						std::cout << "Completion: " << ((double)numSearched)/((double)searchSize)*100.0 << "%" << std::endl;
#endif
						B.makeRandom(b, b1, gen);
						Bnew = B;

						Anew.multiply(Bnew, prod);
						compliance = prod.quadraticCompliance(Nbit);

						if(prod == Nbit) {
							result.success = true;
							result.factors.first = Anew.toSizeT();
							result.factors.second = Bnew.toSizeT();
							std::chrono::high_resolution_clock::time_point stop = clock.now();
							result.duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
							return result;
						}

						for(std::size_t i = 0; i < parameters.Na; i++) {
							for(std::size_t j = 0; j < parameters.Nc; j++) {
								if(choiceDist(gen)) {
									Anew.randomOperation(gen);
								} else {
									Bnew.randomOperation(gen);
								}

								Anew.multiply(Bnew, prod);

								if(prod == Nbit) {
									result.success = true;
									result.factors.first = Anew.toSizeT();
									result.factors.second = Bnew.toSizeT();
									std::chrono::high_resolution_clock::time_point stop = clock.now();
									result.duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
									return result;
								}

								complianceNew = prod.quadraticCompliance(Nbit);
								if(complianceNew > compliance) {
									A = Anew;
									B = Bnew;
									compliance = complianceNew;
								} else {
									if(acceptDist(gen) < exp(((double)(compliance-complianceNew))/(parameters.kB*T))) {
										A = Anew;
										B = Bnew;
										compliance = complianceNew;
									} else {
										Anew = A;
										Bnew = B;
									}
								}

								usedSteps++;
							}

							T *= parameters.Fc;
						}

#ifdef PRIMEFAC_PROGRESS
						numSearched++;
#endif
					}
				}
			}
		}

		std::chrono::high_resolution_clock::time_point stop = clock.now();
		result.duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
		result.usedSteps = usedSteps;

		return result;
	}
	PrimefacResult factorize(const PrimefacParameters& parameters, std::size_t numThreads)
	{
		std::vector<PrimefacThread::Configuration> config = PrimefacThread::createConfigurations(parameters.N, parameters.Nc, parameters.Na, parameters.Fc, parameters.kB, numThreads);
		std::vector<PrimefacThread> threads;
		PrimefacResult result;
		std::chrono::high_resolution_clock clock;
		std::chrono::high_resolution_clock::time_point start = clock.now();

		for(std::size_t i = 0; i < numThreads; i++) {
			threads.push_back(PrimefacThread(config[i]));
		}
		for(std::size_t i = 0; i < numThreads; i++) {
			threads[i].join();
		}

		std::chrono::high_resolution_clock::time_point stop = clock.now();

		result.success = PrimefacThread::getSuccess();
		result.factors = PrimefacThread::getFactors();
		result.usedSteps = PrimefacThread::getUsedSteps();
		result.duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);

		return result;
	}
	SemiprimeResult factorizeSemiprime(const SemiprimeParameters& parameters)
	{
		SemiprimeResult result;
		std::chrono::high_resolution_clock clock;
		std::chrono::high_resolution_clock::time_point start = clock.now();

		std::size_t size = sizeof(std::size_t)*8;
		std::size_t N = parameters.N1*parameters.N2;
		Bitset Nbit(size, N);
		Bitset N1bit(size, parameters.N1);
		Bitset N2bit(size, parameters.N2);
		std::size_t a = N1bit.getRelevant();
		std::size_t b = N2bit.getRelevant();
		std::size_t a1 = N1bit.numOnes();
		std::size_t b1 = N2bit.numOnes();
		std::size_t compliance = 0;
		std::size_t complianceNew = 0;
		Bitset A(size);
		Bitset B(size);
		Bitset Anew(size);
		Bitset Bnew(size);
		Bitset prod(size);
		Prng gen;
		std::uniform_int_distribution<short> choiceDist(0, 1);
		std::uniform_real_distribution<double> acceptDist(0.0, 1.0);
		double T = 1.0;
		std::size_t usedNa = 0;

#ifdef PRIMEFAC_PROGRESS
		std::size_t searchSize = parameters.Na*parameters.Nc;
		std::size_t numSearched = 0;
		std::size_t updateMod = (std::size_t)(0.002*((double)searchSize));
#endif

		A.makeRandom(a, a1,gen);
		Anew = A;
		B.makeRandom(b, b1, gen);
		Bnew = B;

		Anew.multiply(Bnew, prod);
		compliance = prod.quadraticCompliance(Nbit);

		if(prod == Nbit) {
			result.success = true;
			result.factors.first = Anew.toSizeT();
			result.factors.second = Bnew.toSizeT();
			std::chrono::high_resolution_clock::time_point stop = clock.now();
			result.duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
			result.usedNa = usedNa;
			return result;
		}

		T = 1.0;
		for(size_t j = 0; j < parameters.Na; j++) {
#ifdef PRIMEFAC_PROGRESS
			if(numSearched % updateMod == 0) {
				std::cout << "Completion:  " << ((double)numSearched)/((double)searchSize)*100.0 << "%" << std::endl;
			}
#endif
			for(size_t k = 0; k < parameters.Nc; k++) {
				if(choiceDist(gen)) {
					Anew.randomOperation(gen);
				} else {
					Bnew.randomOperation(gen);
				}

				Anew.multiply(Bnew, prod);

				if(prod == Nbit) {
					result.success = true;
					result.factors.first = Anew.toSizeT();
					result.factors.second = Bnew.toSizeT();
					std::chrono::high_resolution_clock::time_point stop = clock.now();
					result.duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
					result.usedNa = usedNa;
					return result;
				}
				complianceNew = prod.quadraticCompliance(Nbit);
				if(complianceNew > compliance) {
					A = Anew;
					B = Bnew;
					compliance = complianceNew;
				} else {
					if(acceptDist(gen) < exp(((double)(compliance-complianceNew))/(parameters.kB*T))) {
						A = Anew;
						B = Bnew;
						compliance = complianceNew;
					} else {
						Anew = A;
						Bnew = B;
					}
				}

#ifdef PRIMEFAC_PROGRESS
				numSearched++;
#endif
			}

			T *= parameters.Fc;
		}

		std::chrono::high_resolution_clock::time_point stop = clock.now();
		result.duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);

		return result;
	}
	SemiprimeResult factorizeSemiprime(const SemiprimeParameters& parameters, std::size_t numThreads)
	{
		std::vector<SemiprimeThread::Configuration> config = SemiprimeThread::createConfigurations(parameters.N1, parameters.N2, parameters.Nc, parameters.Na, parameters.Fc, parameters.kB, numThreads);
		std::vector<SemiprimeThread> threads;
		SemiprimeResult result;
		std::chrono::high_resolution_clock clock;
		std::chrono::high_resolution_clock::time_point start = clock.now();

		for(std::size_t i = 0; i < numThreads; i++) {
			threads.push_back(SemiprimeThread(config[i]));
		}
		for(std::size_t i = 0; i < numThreads; i++) {
			threads[i].join();
		}

		std::chrono::high_resolution_clock::time_point stop = clock.now();

		result.success = SemiprimeThread::getSuccess();
		result.factors = SemiprimeThread::getFactors();
		result.usedNa = SemiprimeThread::getUsedNa();
		result.duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);

		return result;
	}

	std::ostream& operator<<(std::ostream& out, const PrimefacResult& r)
	{
		if(r.success) {
			out << "Success!" << std::endl;
			out << "Factors: " << r.factors.first << " " << r.factors.second << std::endl;
		} else {
			out << "Failure!" << std::endl;
		}
		out << "Duration: " << r.duration.count() << " mus" << std::endl;

		return out;
	}
	std::ostream& operator<<(std::ostream& out, const SemiprimeResult& r)
	{
		if(r.success) {
			out << "Success!" << std::endl;
			out << "Factors: " << r.factors.first << " " << r.factors.second << std::endl;
		} else {
			out << "Failure!" << std::endl;
		}
		out << "Duration: " << r.duration.count() << " mus" << std::endl;

		return out;
	}

	std::ostream& operator<<(std::ostream& out, const PrimefacParameters& p)
	{
		out << "N  = " << p.N  << std::endl;
		out << "Nc = " << p.Nc << std::endl;
		out << "Na = " << p.Na << std::endl;
		out << "Fc = " << p.Fc << std::endl;
		out << "kB = " << p.kB;

		return out;
	}

	std::ostream& operator<<(std::ostream& out, const SemiprimeParameters& p)
	{
		out << "N1 = " << p.N1  << std::endl;
		out << "N2 = " << p.N2  << std::endl;
		out << "N  = " << p.N1*p.N2 << std::endl;
		out << "Nc = " << p.Nc << std::endl;
		out << "Na = " << p.Na << std::endl;
		out << "Fc = " << p.Fc << std::endl;
		out << "kB = " << p.kB;

		return out;
	}

	std::ofstream& operator<<(std::ofstream& out, const PrimefacParameters& p)
	{
		out << "# N  = " << p.N  << std::endl;
		out << "# Nc = " << p.Nc << std::endl;
		out << "# Na = " << p.Na << std::endl;
		out << "# Fc = " << p.Fc << std::endl;
		out << "# kB = " << p.kB;

		return out;
	}

	std::ofstream& operator<<(std::ofstream& out, const SemiprimeParameters& p)
	{
		out << "# N1 = " << p.N1  << std::endl;
		out << "# N2 = " << p.N2  << std::endl;
		out << "# N  = " << p.N1*p.N2 << std::endl;
		out << "# Nc = " << p.Nc << std::endl;
		out << "# Na = " << p.Na << std::endl;
		out << "# Fc = " << p.Fc << std::endl;
		out << "# kB = " << p.kB;

		return out;
	}

}
