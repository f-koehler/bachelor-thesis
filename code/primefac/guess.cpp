#include "guess.hpp"

namespace primefac
{
	double guessBoltzmann(std::size_t N)
	{
		Bitset Nbit(sizeof(std::size_t)*8, N);
		double maxCompliance = (double)Nbit.maxQuadraticCompliance();
		// 8^3/12529
		const double kB0 = 0.040865192752813472743235693191795035517599169925772208476334;
		return maxCompliance*kB0;
	}
}
