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
	SemiprimeParameters parameters;
	parameters.N1 = 71;
	parameters.N2 = 73;
	parameters.Na = 1000;
	parameters.Nc = 1500;
	parameters.Fc = 0.997;
	parameters.kB = 15.0;
	bool guessKB = false;
	size_t numThreads = 1;
	size_t repetitions = 1;
	string fileName("semiprime.txt");

	// parse command line arguments
	for(int arg = 1; arg < argc; arg++) {
		string tmp(argv[arg]);

		if(tmp == "-N1") {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> parameters.N1;
		} else if(tmp == "-N2") {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> parameters.N2;
		} else if(tmp == "-k") {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			tmp = string(argv[arg]);
			if(tmp == "auto") {
				guessKB = true;
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

	if(guessKB) {
		parameters.kB = guessBoltzmann(parameters.N1*parameters.N2);
	}

	ofstream file(fileName.c_str());
	file << parameters << endl;
	file << "#" << endl;
	file << "# run\tsuccess\tduration[mus]\tusedNa" << endl;

	cout << "=====================" << endl;
	cout << " Parameters:" << endl;
	cout << "=====================" << endl;
	cout << parameters << endl;
	if(numThreads > 1) {
		cout << "Threads: " << numThreads << endl;
	}
	cout << endl;
	for(std::size_t i = 0; i < repetitions; i++) {
		cout << "=====================" << endl;
		cout << " Run " << i+1 << "/" << repetitions << ":" << endl;
		cout << "=====================" << endl;
		//SemiprimeResult result = (numThreads <= 1) ? factorizeSemiprime(parameters) : factorizeSemiprime(parameters, numThreads);
		SemiprimeResult result = factorizeSemiprime(parameters, numThreads);
		cout << result << endl << endl;
		file << i << "\t" << result.success << "\t" << result.duration.count() << "\t" << result.usedNa << endl;

		SemiprimeThread::reset();
	}

	file.close();
	
	return EXIT_SUCCESS;
}

void usage()
{
	cout << "semiprime - factorize semiprime numbers using simulated annealing" << endl;
	cout << endl;
	cout << "Usage:" << endl;
	cout << "  primefac [options]" << endl;
	cout << endl;
	cout << "Options:" << endl;
	cout << "  --help       Print this message" << endl;
	cout << "  -N1 [value]  The number to factor, must be larger than 1 and smaller than " << ULONG_MAX << endl;
	cout << "  -N2 [value]  The number to factor, must be larger than 1 and smaller than " << ULONG_MAX << endl;
	cout << "  -k [value]   Value for the Boltzmann constant" << endl;
	cout << "  -Na [value]  Number of annealing steps"  << endl;
	cout << "  -Nc [value]  Number of conifgurations per annealing step" << endl;
	cout << "  -Fc [value]  Cooling factor per annealing step" << endl;
	cout << "  -t [value]   Number of threads" << endl;
	cout << "  -r [value]   Number of repetitions" << endl;
	cout << "  -o [file]    File the results will be written to" << endl;
}
