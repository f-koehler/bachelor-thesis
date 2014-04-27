#include "ising1d.h"
#include <iostream>
#include <vector>
using namespace std;
using namespace ising1d;

void usage();

int main(int argc, char** argv)
{
	// cast arguments in a list of strings
	vector<string> args;
	for(int i = 0; i < argc; i++) {
		args.push_back(string(argv[i]));
	}
	if(argc < 2) {
		usage();
		return EXIT_FAILURE;
	}

	// the second parameter must be either magnetization or temperature
	int argIndex = 1;
	bool modeTemperature = true;
	if(args[argIndex] == std::string("temperature")) {
		modeTemperature = true;
		argIndex++;
	} else if (args[argIndex] == std::string("magnetization")) {
		modeTemperature = false;
		argIndex++;
	} else {
		usage();
		return EXIT_FAILURE;
	}

	// parse all other arguments
	bool cold = false;
	size_t N = 128;
	short spin = 1;
	float start = 0.0f;
	float stop = 5.0f;
	float step = 0.01f;
	size_t balance = 128;
	float J = 1.0f;
	float h = 1.0f;
	float T = 1.0f;
	bool hasJ = false;
	bool hasH = false;
	string log = "ising.txt";
	for(; argIndex < argc; argIndex++) {
		if(args[argIndex] == std::string("-N")) {
			if(argIndex == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			argIndex++;
			istringstream(args[argIndex]) >> N;
		} else if(args[argIndex] == std::string("--spin")) {
			if(argIndex == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			argIndex++;
			istringstream(args[argIndex]) >> spin;
		} else if(args[argIndex] == std::string("--cold")) {
			cold = true;
		} else if(args[argIndex] == std::string("--step")) {
			if(argIndex == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			argIndex++;
			istringstream(args[argIndex]) >> step;
		} else if(args[argIndex] == std::string("--start")) {
			if(argIndex == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			argIndex++;
			istringstream(args[argIndex]) >> start;
		} else if(args[argIndex] == std::string("--stop")) {
			if(argIndex == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			argIndex++;
			istringstream(args[argIndex]) >> stop;
		} else if(args[argIndex] == std::string("--balance")) {
			if(argIndex == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			argIndex++;
			istringstream(args[argIndex]) >> balance;
		} else if(args[argIndex] == std::string("-J")) {
			if(argIndex == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			argIndex++;
			istringstream(args[argIndex]) >> J;
			hasJ = true;
		} else if(args[argIndex] == std::string("-h")) {
			if(argIndex == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			argIndex++;
			istringstream(args[argIndex]) >> h;
			hasH = true;
		} else if(args[argIndex] == std::string("-T")) {
			if(argIndex == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			argIndex++;
			istringstream(args[argIndex]) >> T;
		} else if(args[argIndex] == std::string("-l")) {
			if(argIndex == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			argIndex++;
			log = args[argIndex];
		}
	}

	Ising1d ising(N);

	// configure internal coupling
	if(hasJ) {
		ising.setHasJ(true);
		ising.setJ(J);
	} else {
		ising.setHasJ(false);
		ising.setJ(0.0f);
	}

	// configure external field
	if(hasH) {
		ising.setHasH(true);
		ising.setH(h);
	} else {
		ising.setHasH(false);
		ising.setH(0.0f);
	}
	if(!modeTemperature) {
		ising.setHasH(true);
		ising.setH(start);
	}

	// configure temperature
	ising.setTemperature(T);
	if(modeTemperature) {
		ising.setTemperature(start);
	}

	// generate the lattice
	if(cold) {
		ising.generateColdLattice(spin);
	} else {
		ising.generateHotLattice();
	}

	// do simulation
	ofstream strm(log.c_str());
	T = ising.getTemperature();
	if((start > stop) && (step > 0.0f)) {
		step *= -1;
	}
	for(float walk = start; (step < 0.0f) ? walk >= stop : walk <= stop; walk += step) {
		// do the step
		if(modeTemperature) {
			ising.setTemperature(walk);
		} else {
			ising.setH(walk);
		}

		// do the balance steps
		for(size_t bal = 0; bal < balance; bal++) {
			ising.doMonteCarloStep();
		}
		cout << "T=" << ising.getTemperature() << "\th=" << ising.getH() << "\tU=" << ising.getEnergy() << "\tM=" << ising.getMagnetization() << endl;
		strm << ising.getTemperature() << "\t" << ising.getH() << "\t" << ising.getEnergy() << "\t" << ising.getMagnetization() << endl;
	}
	strm.close();

	return EXIT_SUCCESS;
}

void usage()
{
	cout << "ising1d - a Metropolis Monte sarlo Simulation of the 1d ising model" << endl;
	cout << endl;
	cout << "ising1d temperature [options]" << endl;
	cout << "ising1d magnetization [options]" << endl;
	cout << endl;
	cout << "-N [val]         number of spins" << endl;
	cout << "--spin [val]     spin value" << endl;
	cout << "--cold           create a cold system where all spins are parallel" << endl;
	cout << "--start [val]    starting value of the parameter" << endl;
	cout << "--stop  [val]    stop value of the parameter" << endl;
	cout << "--step  [val]    stepwidth for the parameter change" << endl;
	cout << "--balance [val]  balance steps to reach equilibirum" << endl;
	cout << "-h [val]         strength of the external field" << endl;
	cout << "-J [val]         strength of the internal coupling" << endl;
	cout << "-T [val]         temperature of the system" << endl;
	cout << "-l [val]         file where to store the values" << endl;
}
