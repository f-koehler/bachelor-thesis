#ifndef BITSET_HPP_
#define BITSET_HPP_

#include <ostream>
#include <sstream>
#include <vector>
#include <random>
#include <cstring>

namespace primefac
{

	typedef std::mt19937 Prng;
	
	class Bitset
	{
		private:
			bool*  set;
			unsigned long setSize;
			unsigned long relevant;
			std::uniform_int_distribution<std::size_t> indexDistribution;

		public:
			Bitset(std::size_t size, bool val = true);
			Bitset(std::size_t size, std::size_t number);
			Bitset(std::size_t size, std::size_t numRelevant, std::size_t numOnes, Prng& gen);
			Bitset(const Bitset& bits);
			virtual ~Bitset();

			void makeRandom(std::size_t numRelevant, std::size_t numOnes, Prng& gen);

			void swapBits(std::size_t i, std::size_t j);
			void reverseSequence(std::size_t start, std::size_t end);
			void slideSequence(std::size_t start, std::size_t end);
			void multiply(const Bitset& a, Bitset& result) const;

			void randomOperation(Prng& gen);

			std::size_t getSize() const;
			std::size_t getRelevant() const;
			std::size_t toSizeT() const;
			std::size_t linearCompliance(const Bitset& bits) const;
			std::size_t quadraticCompliance(const Bitset& bits) const;
			std::size_t maxLinearCompliance() const;
			std::size_t maxQuadraticCompliance() const;

			bool& operator[](std::size_t index);
			const bool& operator[](std::size_t index) const;
			Bitset& operator=(const Bitset& bits);
			bool operator==(const Bitset& bits) const;
			bool operator!=(const Bitset& bits) const;

			friend std::ostream& operator<<(std::ostream& out, const Bitset& bits);
	};

	std::ostream& operator<<(std::ostream& out, const Bitset& bits);
}

#endif
