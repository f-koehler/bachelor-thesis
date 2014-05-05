#ifndef SEED_HPP_
#define SEED_HPP_

#include "config.hpp"
#include <random>

namespace primefac
{
	/**
	 * Reads a seed from a random device (a hardware random number generator)
	 * @return A random seed.
	 */
	Prng::result_type readSeed();
}

#endif
