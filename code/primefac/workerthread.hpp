#ifndef WORKERTHREAD_HPP_
#define WORKERTHREAD_HPP_

#include "bitset.hpp"
#include <thread>

namespace primefac
{

	class WorkerThread
	{
		public:
			typedef struct {
				std::size_t N;
				std::size_t Na;
				std::size_t Nc;
				double Fc;
			} Configuration;

		private:
			std::size_t threadId;

			Configuration cfg;

			std::size_t n;
			std::size_t a;
			std::size_t b;
			std::size_t a1;
			std::size_t b1;

			Bitset Nbits;
			Bitset Abits;
			Bitset Bits;
			Bitset ANewBits;
			Bitset BNewBits;

		public:
			WorkerThread(Configuration& config);
	};

}

#endif
