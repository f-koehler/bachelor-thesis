#include "bitset.hpp"

namespace primefac {

	Bitset::Bitset(std::size_t size, bool val)
	{
		setSize = size;
		set = new bool[setSize];

		if(val) {
			relevant = setSize;
		} else {
			relevant = 1;
		}

		if(relevant <= 2) {
			indexDistribution = std::uniform_int_distribution<std::size_t>(0, 0);
		} else {
			indexDistribution = std::uniform_int_distribution<std::size_t>(0, relevant-2);
		}

		for(std::size_t i = 0; i < setSize; i++) {
			set[i] = val;
		}
	}
	Bitset::Bitset(std::size_t size, std::size_t number)
	{
		setSize = size;
		set = new bool[setSize];

		std::size_t i = 0;
		while(((number != 0) || (i == 0)) && (i < setSize)) {
			set[i] = (bool)(number % 2);
			number /= 2;
			i++;
		}

		relevant = i;

		if(relevant <= 2) {
			indexDistribution = std::uniform_int_distribution<std::size_t>(0, 0);
		} else {
			indexDistribution = std::uniform_int_distribution<std::size_t>(0, relevant-2);
		}
	}
	Bitset::Bitset(std::size_t size, std::size_t numRelevant, std::size_t numOnes, Prng& gen)
	{
		setSize = size;
		set = new bool[setSize];
		relevant = numRelevant;

		std::size_t i = 0;
		for(i = 0; i < numOnes-1; i++) {
			set[i] = true;
		}
		for(i = numOnes-1; i < numRelevant-1; i++) {
			set[i] =false;
		}
		set[numRelevant-1] = true;

		if(relevant <= 2) {
			indexDistribution = std::uniform_int_distribution<std::size_t>(0, 0);
		} else {
			indexDistribution = std::uniform_int_distribution<std::size_t>(0, relevant-2);
		}

		for(i = 0; i < setSize-1; i++) {
			swapBits(indexDistribution(gen), indexDistribution(gen));
		}
	}
	Bitset::Bitset(const Bitset& bits)
	{
		setSize = bits.setSize;
		set = new bool[setSize];
		relevant = bits.relevant;
		for(std::size_t i = 0; i < setSize; i++) {
			set[i] = bits.set[i];
		}
		indexDistribution = bits.indexDistribution;
	}
	Bitset::~Bitset()
	{
		if(set) {
			delete[] set;
		}
	}
	
	void Bitset::makeRandom(std::size_t numRelevant, std::size_t numOnes, Prng& gen)
	{
		relevant = numRelevant;
		std::size_t i = 0;
		for(i = 0; i < numOnes-1; i++) {
			set[i] = true;
		}
		for(i = numOnes-1; i < numRelevant-1; i++) {
			set[i] =false;
		}
		set[numRelevant-1] = true;

		if(relevant <= 2) {
			indexDistribution = std::uniform_int_distribution<std::size_t>(0, 0);
		} else {
			indexDistribution = std::uniform_int_distribution<std::size_t>(0, relevant-2);
		}

		for(i = 0; i < setSize-1; i++) {
			swapBits(indexDistribution(gen), indexDistribution(gen));
		}
	}

	void Bitset::swapBits(std::size_t i, std::size_t j)
	{
		bool tmp = set[i];
		set[i] = set[j];
		set[j] = tmp;
	}
	void Bitset::reverseSequence(std::size_t start, std::size_t end)
	{
		if(start > end) {
			std::size_t tmp = start;
			start = end;
			end = tmp;
		}
		std::size_t count = (end-start)/2+1;
		for(std::size_t i = 0; i < count; i++) {
			swapBits(start+i, end-i);
		}
	}
	void Bitset::slideSequence(std::size_t start, std::size_t end)
	{
		if(start > end) {
			std::size_t tmp = start;
			start = end;
			end = tmp;
		}
		bool tmp = set[start];
		for(std::size_t i = start; i < end; i++) {
			set[i] = set[i+1];
		}
		set[end] = tmp;
	}
	void Bitset::sparsePermutation(Prng& gen)
	{	
		/*std::uniform_int_distribution<std::size_t> numDist(0, setSize-1);
		std::size_t count = numDist(gen);
		for(std::size_t i = 0; i < count; i++) {
		swapBits(indexDistribution(gen), indexDistribution(gen));
		}*/
		std::vector<bool> values;
		std::vector<std::size_t> positions;
		double p = 0.0;
		double pSel = 1.0/((double)relevant);
		std::uniform_real_distribution<double> dist;

		for(size_t i = 0; i < relevant-1; i++) {
			p = dist(gen);
			if(p < pSel) {
				positions.push_back(i);
				values.push_back(set[i]);
			}
		}

		std::shuffle(values.begin(), values.end(), gen);
		std::size_t numSel = values.size();

		for(std::size_t i = 0; i < numSel; i++) {
			set[positions[i]] = values[i];
		}
	}

	void Bitset::multiply(const Bitset& a, Bitset& result) const
	{
		memset((void*)result.set, 0, result.setSize*sizeof(bool));

		bool overhead = false;
		std::size_t pos = 0;
		for(std::size_t i = 0; i < relevant; i++) {
			for(std::size_t j = 0; j < a.relevant; j++) {
				pos = i+j;	
				if(set[i] && a.set[j]) {
					if(result.set[pos]) {
						result.set[pos] = false;
						overhead = true;
					} else {
						result.set[pos] = true;
						overhead = false;
					}
				}

				while(overhead) {
					pos++;

					if(!result.set[pos]) {
						result.set[pos] = true;
						overhead = false;
					} else {
						result.set[pos] = false;
					}
				}
			}
		}

		std::size_t newRel = relevant+a.relevant;
		if(!result.set[newRel-1]) {
			newRel--;
		}
		if(!result.set[newRel-1]) {
			newRel--;
		}
		result.relevant = newRel;
	}
	
	void Bitset::randomOperation(Prng& gen)
	{
		std::uniform_int_distribution<std::size_t> opDist(0, 3);
		std::size_t choice = opDist(gen);

		switch(choice) {
			case 0:
				swapBits(indexDistribution(gen), indexDistribution(gen));
				break;
			case 1:
				reverseSequence(indexDistribution(gen), indexDistribution(gen));
				break;
			case 2:
				slideSequence(indexDistribution(gen), indexDistribution(gen));
				break;
			default:
				sparsePermutation(gen);

		}
	}

	std::size_t Bitset::getSize() const
	{
		return setSize;
	}
	std::size_t Bitset::getRelevant() const
	{
		return relevant;
	}
	std::size_t Bitset::toSizeT() const
	{
		if(setSize > sizeof(std::size_t)*8) {
			return 0;
		}

		size_t ret = 0;
		size_t base = 1;
		for(size_t i = 0; i < relevant; i++) {
			if(set[i]) {
				ret += base;
			}
			base *= 2;
		}
		return ret;
	}
	std::size_t Bitset::linearCompliance(const Bitset& bits) const
	{
		size_t comp = 0;
		size_t len = (relevant < bits.relevant) ? relevant : bits.relevant;
		for(size_t i = 0; i < len; i++) {
			if(set[i] == bits.set[i]) {
				comp += i+1;
			}
		}

		return comp;
	}
	std::size_t Bitset::quadraticCompliance(const Bitset& bits) const
	{
		size_t comp = 0;
		size_t len = (relevant < bits.relevant) ? relevant : bits.relevant;
		for(size_t i = 0; i < len; i++) {
			if(set[i] == bits.set[i]) {
				comp += (i+1)*(i+1);
			}
		}

		return comp;
	}
	std::size_t Bitset::maxLinearCompliance() const
	{
		return linearCompliance(*this);
	}
	std::size_t Bitset::maxQuadraticCompliance() const
	{
		return quadraticCompliance(*this);
	}
	std::size_t Bitset::numOnes() const
	{
		std::size_t num = 0;
		for(std::size_t i = 0; i < relevant; i++) {
			if(set[i]) {
				num++;
			}
		}
		return num;
	}

	bool& Bitset::operator[](std::size_t index)
	{
		return set[index];
	}

	const bool& Bitset::operator[](std::size_t index) const
	{
		return set[index];
	}
	Bitset& Bitset::operator=(const Bitset& bits)
	{
		if(set && (setSize != bits.setSize)) {
			delete[] set;
			setSize = bits.setSize;
			set = new bool[setSize];
		}
		for(std::size_t i = 0; i < setSize; i++) {
			set[i] = bits.set[i];
		}
		relevant = bits.relevant;
		indexDistribution = bits.indexDistribution;

		return *this;
	}
	bool Bitset::operator==(const Bitset& bits) const
	{
		if(relevant != bits.relevant) {
			return false;
		}

		for(std::size_t i = 0; i < relevant; i++) {
			if(set[i] != bits.set[i]) {
				return false;
			}
		}

		return true;
	}
	bool Bitset::operator!=(const Bitset& bits) const
	{
		if(relevant != bits.relevant) {
			return true;
		}
		
		for(std::size_t i = 0; i < relevant; i++) {
			if(set[i] != bits.set[i]) {
				return true;
			}
		}

		return false;
	}

	std::ostream& operator<<(std::ostream& out, const Bitset& bits)
	{
		for(std::size_t i = bits.relevant-1; i >= 1; i--) {
			out << bits.set[i];
		}
		out << bits.set[0];
		return out;
	}
}
