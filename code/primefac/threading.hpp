#ifndef THREADING_HPP_
#define THREADING_HPP_

#include "config.hpp"
#include "bitset.hpp"
#include "seed.hpp"
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <cmath>

namespace primefac
{
	typedef struct {
		/** N, the number to factorize */
		std::size_t number;

		/** Nc, the number of configurations per annealing step */
		std::size_t numConfigurations;

		/** Na, the number of annealing steps */
		std::size_t numAnnealingSteps;

		/** Fc, the cooling factor */
		double coolingFactor;

		/** kB, the Boltzmann constant */
		double kB = 0.0;


		/** The ID of the corresponding thread */
		std::size_t threadId;

		/** The number of threads to use */
		std::size_t numThreads;
	} PrimefacConfiguration;

	typedef struct {
		/** The first factor of the semiprime number */
		std::size_t prime1;

		/** The second factor of the semiprime number */
		std::size_t prime2;

		/** Nc, the number of configurations per annealing step */
		std::size_t numConfigurations;

		/** Na, the number of annealing steps */
		std::size_t numAnnealingSteps;

		/** Fc, the cooling factor */
		double coolingFactor;

		/** kB, the Boltzmann constant */
		double kB = 0.0;


		/** The ID of the corresponding thread */
		std::size_t threadId;

		/** The number of threads to use */
		std::size_t numThreads;
	} SemiprimeConfiguration;

	std::vector<PrimefacConfiguration> createPrimefacConfigurations(
			std::size_t number, std::size_t numConfigurations,
			std::size_t numAnnealingSteps, double coolingFactor,
			double kB, std::size_t numThreads);
	std::vector<SemiprimeConfiguration> createSemiprimeConfigurations(
			std::size_t prime1, std::size_t prime2,
			std::size_t numConfigurations, std::size_t numAnnealingSteps,
			double coolingFactor, double kB, std::size_t numThreads);

	void primefacThreadFunc(const PrimefacConfiguration& config);
	void semiprimeThreadFunc(const SemiprimeConfiguration& config);
}

#endif
