#ifndef PRIMEFAC_HPP_
#define PRIMEFAC_HPP_

#include "config.hpp"
#include "threading.hpp"
#include <vector>
#include <utility>
#include <chrono>
#include <cmath>

namespace primefac
{
	typedef struct {
		std::size_t N;
		std::size_t Nc;
		std::size_t Na;
		double Fc;
		double kB;
	} PrimefacParameters;

	typedef struct {
		bool success;
		std::vector<std::size_t> factors;
		std::chrono::microseconds duration;
	} PrimefacResult;

	typedef struct {
		std::size_t N1;
		std::size_t N2;
		std::size_t Nc;
		std::size_t Na;
		double Fc;
		double kB;
	} SemiprimeParameters;

	typedef struct {
		bool success;
		std::pair<std::size_t, std::size_t> factors;
		std::chrono::microseconds duration;
	} SemiprimeResult;

	PrimefacResult factorize(const PrimefacParameters& parameters);
	PrimefacResult factorize(const PrimefacParameters& parameters, std::size_t numThreads);
	SemiprimeResult factorizeSemiprime(const SemiprimeParameters& parameters);
	SemiprimeResult factorizeSemiprime(const SemiprimeParameters& parameters, std::size_t numThreads);
}

#endif
