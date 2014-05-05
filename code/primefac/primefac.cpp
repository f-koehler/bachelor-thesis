#include "primefac.hpp"

namespace primefac
{
	PrimefacResult factorize(const PrimefacParameters& parameters)
	{
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

		result.success = false;
		for(std::size_t i = 0; i < numThreads; i++) {
			if(threads[i].getSuccess()) {
				result.success = true;
				result.factors = threads[i].getFactors();
				break;
			}
		}

		result.duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);

		return result;
	}
	SemiprimeResult factorizeSemiprime(const SemiprimeParameters& parameters)
	{
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

		result.success = false;
		for(std::size_t i = 0; i < numThreads; i++) {
			if(threads[i].getSuccess()) {
				result.success = true;
				result.factors = threads[i].getFactors();
				break;
			}
		}

		result.duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);

		return result;
	}
}
