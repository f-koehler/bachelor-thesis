#ifndef ISING1D_H_
#define ISING1D_H_

#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>

namespace ising1d {

	class Ising1d {
		private:
			// the hamilton operator
			bool  has_h;
			bool  has_j;
			float h;
			float j;

			// a table to lookup energy changes due to spin flips
			float flipEnergy[8];
			float flipProbability[8];

			// the lattice
			short* spins;
			size_t size;
			float  t;
			float  energy;
			long   magnetization;

			// random number generator
			boost::random::mt19937 mt;

			// a uniform distribution to select a random spin
			boost::random::uniform_int_distribution<> indexDist;

		public:
			Ising1d(size_t N);
			virtual ~Ising1d();

			// methods to prepare the simulation
			void prepareEnergyLookup();
			void prepareProbabilityLookup();
			void newSeed();
			void generateColdLattice(short spin = 1);
			void generateHotLattice();
			void applyHamiltonian();
			void calcMagnetization();

			// lattice navigation
			short  getLeftSpin(size_t index) const;
			short  getRightSpin(size_t index) const;
			size_t getLeftIndex(size_t index) const;
			size_t getRightIndex(size_t index) const;

			// MonteCarlo functions
			void flipMetropolis();
			void doMonteCarloStep();

			// get and set methods
			bool   hasJ() const;
			bool   hasH() const;
			float  getJ() const;
			float  getH() const;
			float  getTemperature() const;
			float  getEnergy() const;
			long   getMagnetization() const;
			float  getFlipEnergy(short a, short b, short c) const;
			float  getFlipProbability(short a, short b, short c) const;
			void   setHasJ(bool val);
			void   setHasH(bool val);
			void   setJ(float J);
			void   setH(float H);
			void   setTemperature(float temperature);

			// string conversions
			std::string hamiltonianString() const;
			std::string latticeString() const;
	};

}

#endif
