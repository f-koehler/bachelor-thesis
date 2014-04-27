#include "seed.hpp"

namespace primefac {

	std::size_t readSeed() {
		std::ifstream strm("/dev/random", std::ios_base::in | std::ios_base::binary);
		std::size_t seed = 0;
		strm.read((char*)&seed, sizeof(std::size_t));
		strm.close();
		return seed;
	}

}
