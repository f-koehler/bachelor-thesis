#ifndef BITSET_HPP_
#define BITSET_HPP_

#include "config.hpp"
#include <ostream>
#include <vector>
#include <algorithm>
#include <cstring>

namespace primefac
{
	/** @brief A class representing bitsets, specially designed for the task of factorization using simulated annealing. */
	class Bitset
	{
		private:
			/** A bool field that represents the bitset */
			bool*  set;

			/** The size of the array set */
			unsigned long setSize;

			/** The number of bits that are not leading zeros. */
			unsigned long relevant;

			/** A distribution for random numbers to chose random indices with respect to the need of leading one. */
			std::uniform_int_distribution<std::size_t> indexDistribution;

		public:
			/**
			 * Constructor that will create a Bitset of given size and initialize it with a value.
			 * @param[in] size The size of the field that will store the bool's
			 * @param[in] val  The default value that all bool's will have afer construction, defaults to true
			 */
			Bitset(std::size_t size, bool val = true);

			/**
			 * Constructor that will create a Bitset from a number.
			 * @param[in] size The size of the field that will store the bool's
			 * @param[in] number The number that will be converted to binary represntation
			 */
			Bitset(std::size_t size, std::size_t number);

			/**
			 * Constructor that will create a random Bitset.
			 * @param[in] size The size of the field that will store the bool's
			 * @param[in] numRelevant The length of the binary number. All other bits will be leading zeros
			 * @param[in,out] gen The random number generator to be used
			 */
			Bitset(std::size_t size, std::size_t numRelevant, std::size_t numOnes, Prng& gen);

			/**
			 * Copy-Constructor that will copy an existing Bitset.
			 * @param[in] bits The Bitset to copy.
			 */
			Bitset(const Bitset& bits);
			
			/**
			 * Destructor
			 */
			virtual ~Bitset();


			/**
			 * Randomize the Bitset. The size will not change.
			 * @param[in] size The size of the field that will store the bool's
			 * @param[in] numRelevant The length of the binary number. All other bits will be leading zeros
			 * @param[in,out] gen The random number generator to be used
			 */
			void makeRandom(std::size_t numRelevant, std::size_t numOnes, Prng& gen);


			/**
			 * Swap two bits in the Bitset.
			 * @param[in] i Index of first bit
			 * @param[in] j Index of second bit
			 */
			void swapBits(std::size_t i, std::size_t j);

			/**
			 * Reverse a sequence of bits.
			 * @param[in] start The starting index of the sequence
			 * @param[in] stop The starting index of the sequence
			 */
			void reverseSequence(std::size_t start, std::size_t end);

			/**
			 * In the sequence of bits remove the rightmost bit, slide all remaining bits to the left, and insert the removed bit where the leftmost was
			 * @param[in] start The starting index of the sequence
			 * @param[in] stop The starting index of the sequence
			 */
			void slideSequence(std::size_t start, std::size_t end);

			/**
			 * Select random sparse elements and permute them randomly.
			 * @param[in, out] gen The random number generator to use.
			 */
			void sparsePermutation(Prng& gen);

			/**
			 * Multiply this Bitset with another one on the binary level.
			 * @param[in] a The Bitset this one will be multiplied with
			 * @param[out] result The result of the multiplication will be written into this Bitset
			 */
			void multiply(const Bitset& a, Bitset& result) const;


			/**
			 * Choose one of these operations randomly: Bitset::swapBits Bitset::reverseSequence Bitset::slideSequence or will do a random sparse permutation. The parameters for this peration are randomly chosen.
			 * @param[in,out] gen The random number generator to be used
			 */
			void randomOperation(Prng& gen);


			/**
			 * Return the the size of the bool field.
			 * @return The size of the bool field-
			 */
			std::size_t getSize() const;

			/**
			 * Return the the number of relevant bits or in other word the number of bits that are not leading zeros.
			 * @return The number of relevant bits.
			 */
			std::size_t getRelevant() const;
			
			/**
			 * Convert the Bitset to a number.
			 * @return The number this Bitset represents.
			 */
			std::size_t toSizeT() const;

			/**
			 * Compute the linear compliance to another Bitset.
			 * @param[in] bits The Bitset this one will be compared to
			 * @return Linear compliance to  bits
			 */
			std::size_t linearCompliance(const Bitset& bits) const;

			/**
			 * Compute the quadratic compliance to another Bitset.
			 * @param[in] bits The Bitset this one will be compared to
			 * @return Linear compliance to  bits
			 */
			std::size_t quadraticCompliance(const Bitset& bits) const;

			/**
			 * Calculate the maximum lineare compliance another bitset could have regarding this one.
			 * @return The maximum linear compliance
			 */
			std::size_t maxLinearCompliance() const;

			/**
			 * Calculate the maximum quadratic compliance another bitset could have regarding this one.
			 * @return The maximum quadratic compliance
			 */
			std::size_t maxQuadraticCompliance() const;

			/**
			 * Return the number of ones in the Bitset.
			 * @return The number of ones set.
			 */
			std::size_t numOnes() const;


			/**
			 * Operator overload to access the bits via [].
			 * @param index The index in the field to access;
			 * @return A reference to the field element.
			 */
			bool& operator[](std::size_t index);

			/**
			 * Operator overload to access the bits via []. Read-only version for const instances of the class.
			 * @param[in] index The index in the field to access;
			 * @return A const reference to the field element.
			 */
			const bool& operator[](std::size_t index) const;

			/**
			 * Assign operator overload.
			 * @param[in] bits The Bitset this one will be set to.
			 * @return a reference to this Bitset that represents the same as bits.
			 */
			Bitset& operator=(const Bitset& bits);

			/**
			 * Operator overload for the equality operator. This will first check if the lengths of both Bitsets are equal and if so compare them bitwise.
			 * @return true if both Bitsets are equal by length and bitwise, otherwise false
			 */
			bool operator==(const Bitset& bits) const;

			/**
			 * Operator overload for the inequality operator. This will first check if the lengths of both Bitsets are equal and if so compare them bitwise.
			 * @return false if both Bitsets are equal by length and bitwise, otherwise true
			 */
			bool operator!=(const Bitset& bits) const;


			friend std::ostream& operator<<(std::ostream& out, const Bitset& bits);
	};

	/**
	 * Write a Bitset to an ostream, e.g. cout or an ofstream
	 * @param[in, out] out The stream that the Bitset will be written to
	 * @param[in] bits The Bitset to write
	 * @return A reference to the ostream out
	 */
	std::ostream& operator<<(std::ostream& out, const Bitset& bits);
}

#endif
