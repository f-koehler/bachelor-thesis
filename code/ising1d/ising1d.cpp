#include "ising1d.h"

namespace ising1d {
	Ising1d::Ising1d(size_t N) :
		mt(), indexDist(0, N-1)
	{
		// default hamiltonian
		has_j = true;
		has_h = true;
		j     = 1.0f;
		h     = 1.0f;

		// prepare the energy lookup table
		prepareEnergyLookup();

		// create the lattice
		size  = N;
		spins = new short[size];
		t     = 1.0f;

		// generate a cold system
		generateColdLattice();

		// read a seed for the merssenne twister
		newSeed();
	}
	Ising1d::~Ising1d()
	{
		if(spins) {
			delete[] spins;
		}
	}

	// methods to prepare the simulation
	void Ising1d::prepareEnergyLookup()
	{
		short aSpin = 0;
		short bSpin = 0;
		short cSpin = 0;
		short index = 0;
		for(short a = 0; a <= 1; a++) {
			aSpin = a*2-1;
			for(short b = 0; b <= 1; b++) {
				bSpin = b*2-1;
				for(short c = 0; c <= 1; c++) {
					cSpin = c*2-1;
					index = a*4+b*2+c;
					flipEnergy[index] = 0.0f;
					if(has_h) {
						flipEnergy[index] += h*((float)bSpin);
					}
					if(has_j) {
						flipEnergy[index] += j*((float)(aSpin*bSpin+bSpin*cSpin));
					}
					flipEnergy[index] *= 2.0f;
				}
			}
		}
		prepareProbabilityLookup();
	}
	void Ising1d::prepareProbabilityLookup() {
		for(size_t i = 0; i < 8; i++) {
			flipProbability[i] = exp(-flipEnergy[i]/t);
		}
	}
	void Ising1d::newSeed()
	{
		std::ifstream strm("/dev/random", std::ios_base::in | std::ios_base::binary);
		unsigned int seed;
		strm.read((char*)&seed, sizeof(unsigned int));
		mt.seed(seed);
	}
	void Ising1d::generateColdLattice(short spin)
	{
		for(size_t i = 0; i < size; i++) {
			spins[i] = spin;
		}

		// calculate initial magnetization and energy
		applyHamiltonian();
		calcMagnetization();
	}
	void Ising1d::generateHotLattice()
	{
		boost::random::uniform_int_distribution<> spinDist(0, 1);
		for(size_t i = 0; i < size; i++) {
			spins[i] = spinDist(mt)*2-1;
		}

		// calculate initial magnetization and energy
		applyHamiltonian();
		calcMagnetization();
	}
	void Ising1d::applyHamiltonian()
	{
		float coupling = 0.0f;
		float field = 0.0f;
		energy = 0.0f;

		for(size_t i = 0; i < size; i++) {
			if(has_h) {
				field += (float)(spins[i]);
			}
			if(has_j) {
				coupling += (float)(spins[i]*getLeftSpin(i)+spins[i]*getRightSpin(i));
			}
		}
		if(has_h) {
			field *= -h;
			energy += field;
		}
		if(has_j) {
			coupling *= -(j/2.0f);
			energy += coupling;
		}
	}
	void Ising1d::calcMagnetization()
	{
		magnetization = 0;
		for(size_t i = 0; i < size; i++) {
			magnetization += (long)spins[i];
		}
	}

	// lattice navigation
	short Ising1d::getLeftSpin(size_t index) const
	{
		if(index == 0) {
			return spins[size-1];
		} else {
			return spins[index-1];
		}
	}
	short Ising1d::getRightSpin(size_t index) const
	{
		if(index == size-1) {
			return spins[0];
		} else {
			return spins[index+1];
		}
	}
	size_t Ising1d::getLeftIndex(size_t index) const
	{
		if(index == 0) {
			return size-1;
		} else {
			return index-1;
		}
	}
	size_t Ising1d::getRightIndex(size_t index) const
	{
		if(index == size-1) {
			return 0;
		} else {
			return index+1;
		}
	}

	// MonteCarlo functions
	void Ising1d::flipMetropolis()
	{
		size_t index = indexDist(mt);
		short aSpin  = getLeftSpin(index);
		short bSpin  = spins[index];
		short cSpin  = getRightSpin(index);
		float dE     = getFlipEnergy(aSpin, bSpin, cSpin);
		if(dE < 0.0f) {
			spins[index] *= -1;
			energy += dE;
			magnetization += -2*bSpin;
			return;
		}
		boost::random::uniform_real_distribution<> xDist(0, 1);
		float p = getFlipProbability(aSpin, bSpin, cSpin);
		float x = xDist(mt);
		if(x < p) {
			spins[index] *= -1;
			energy += dE;
			magnetization += -2*bSpin;
		}
	}
	void Ising1d::doMonteCarloStep()
	{
		for(size_t i = 0; i < size; i++) {
			flipMetropolis();
		}
	}

	// get and set methods
	bool Ising1d::hasJ() const
	{
		return has_j;
	}
	bool Ising1d::hasH() const
	{
		return has_h;
	}
	float Ising1d::getJ() const
	{
		return j;
	}
	float Ising1d::getH() const
	{
		return h;
	}
	float Ising1d::getTemperature() const
	{
		return t;
	}
	float Ising1d::getEnergy() const
	{
		return energy;
	}
	long Ising1d::getMagnetization() const
	{
		return magnetization;
	}
	float Ising1d::getFlipEnergy(short a, short b, short c) const
	{
		return flipEnergy[(a+1)*2+(b+1)+(c+1)/2];
	}
	float Ising1d::getFlipProbability(short a, short b, short c) const
	{
		return flipProbability[(a+1)*2+(b+1)+(c+1)/2];
	}
	void Ising1d::setHasJ(bool val)
	{
		has_j = val;
		applyHamiltonian();
		prepareEnergyLookup();
	}
	void Ising1d::setHasH(bool val)
	{
		has_h = val;
		applyHamiltonian();
		prepareEnergyLookup();
	}
	void Ising1d::setJ(float J)
	{
		j = J;
		applyHamiltonian();
		prepareEnergyLookup();
	}
	void Ising1d::setH(float H)
	{
		h = H;
		applyHamiltonian();
		prepareEnergyLookup();
	}
	void Ising1d::setTemperature(float temperature)
	{
		t = temperature;
		prepareProbabilityLookup();
	}

	// string conversions
	std::string Ising1d::hamiltonianString() const
	{
		std::stringstream strm;
		strm << "hasH=" << has_h << " hasJ=" << has_j << " h=" << h << " j=" << j;
		return strm.str();
	}
	std::string Ising1d::latticeString() const
	{
		std::stringstream strm;
		for(size_t i = 0; i < size; i++) {
			strm << spins[i] << " ";
		}
		return strm.str();
	}
}
