#ifndef THREADING_HPP_
#define THREADING_HPP_

#include "bitset.hpp"
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <cmath>

namespace primefac
{
	typedef struct {
		std::size_t number;
		std::size_t numConfigurations;
		std::size_t numAnnealingSteps;
		double coolingFactor;
		double kB = 0.0;

		std::size_t threadId;
		std::size_t numThreads;
	} PrimefacConfiguration;

	std::vector<PrimefacConfiguration> createPrimefacConfigurations(
			std::size_t number, std::size_t numConfigurations,
			std::size_t numAnnealingSteps, double coolingFactor,
			double kB, std::size_t numThreads);
	void primefacThreadFunc(const PrimefacConfiguration& config);
}

#endif
