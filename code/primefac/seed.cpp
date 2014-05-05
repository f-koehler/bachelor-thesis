#include "seed.hpp"

namespace primefac
{
	Prng::result_type readSeed()
	{
		std::random_device dev;
		return dev();
	}
}
