#include "primefac.hpp"
#include "guess.hpp"
#include <sstream>
#include <climits>
using namespace primefac;
using namespace std;

void usage();

int main(int argc, char** argv)
{
	// standard simulation parameters
	PrimefacParameters parameters;
	parameters.N = 100;
	parameters.Na = 1000;
	parameters.Nc = 1500;
	parameters.Fc = 0.997;
	parameters.kB = 15.0;
	bool guessKb = false;
	size_t numThreads = 0;
	size_t repetitions = 1;
	string fileName("onestep.txt");

	// parse command line arguments
	for(int arg = 1; arg < argc; arg++) {
		string tmp(argv[arg]);

		if(tmp == "-N") {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> parameters.N;
		} else if(tmp == "-k") {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			tmp = string(argv[arg]);
			if(tmp == "auto") {
				guessKb = true;
			} else {
				stringstream(tmp) >> parameters.kB;
			}
		} else if(tmp == "-Na") {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> parameters.Na;
		} else if(tmp == "-Nc") {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> parameters.Nc;
		} else if(tmp == "-Fc") {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> parameters.Fc;
		} else if(tmp == "-t") {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> numThreads;
		} else if(tmp == "-r") {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> repetitions;
		} else if(tmp == "-o") {
			if(arg == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			fileName = string(argv[arg]);
		} else if(tmp == "--help") {
			usage();
			return EXIT_FAILURE;
		} else {
			cerr << "Unknown argument \"" << tmp << "\"!" << endl << endl;;
			usage();
			return EXIT_FAILURE;
		}
	}

	if(guessKb) {
		parameters.kB = guessBoltzmann(parameters.N);
	}

	ofstream file(fileName.c_str());
	file << parameters << endl;
	file << "#" << endl;
	file << "# run\tsuccess\tduration[mus]\tusedSteps" << endl;

	cout << "=====================" << endl;
	cout << " Parameters:" << endl;
	cout << "=====================" << endl;
	cout << parameters << endl;
	if(numThreads > 1) {
		cout << "Threads: " << numThreads << endl;
	}
	cout << endl;
	for(size_t i = 0; i < repetitions; i++) {
		cout << "=====================" << endl;
		cout << " Run " << i+1 << "/" << repetitions << ":" << endl;
		cout << "=====================" << endl;
		PrimefacResult result = (numThreads <= 1) ? factorize(parameters) : factorize(parameters, numThreads);
		cout << result << endl << endl;
		file << i << "\t" << result.success << "\t" << result.duration.count() << "\t" << result.usedSteps << endl;

		PrimefacThread::reset();
	}

	file.close();

	return EXIT_SUCCESS;
}

void usage()
{
	cout << "primefac - factorize numbers using simulated annealing" << endl;
	cout << endl;
	cout << "Usage:" << endl;
	cout << "  primefac [options]" << endl;
	cout << endl;
	cout << "Options:" << endl;
	cout << "  --help       Print this message" << endl;
	cout << "  -N [value]   The number to factor, must be larger than 1 and smaller than " << ULONG_MAX << endl;
	cout << "  -k [value]   Value for the Boltzmann constant" << endl;
	cout << "  -Na [value]  Number of annealing steps"  << endl;
	cout << "  -Nc [value]  Number of conifgurations per annealing step" << endl;
	cout << "  -Fc [value]  Cooling factor per annealing step" << endl;
	cout << "  -t [value]   Number of threads" << endl;
	cout << "  -r [value]   Number of repetitions" << endl;
	cout << "  -o [file]    File the results will be written to" << endl;
}
