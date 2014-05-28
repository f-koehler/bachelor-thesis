#include "primefac.hpp"
#include "guess.hpp"
#include "sieve.hpp"
#include <stack>
#include <sstream>
#include <climits>
using namespace primefac;
using namespace std;

void usage();

int main(int argc, char** argv)
{
	// standard simulation parameters
	PrimefacParameters parameters;
	size_t N = 100;
	parameters.N = 100;
	parameters.Na = 1000;
	parameters.Nc = 1500;
	parameters.Fc = 0.997;
	parameters.kB = 15.0;
	size_t numThreads = 0;
	size_t repetitions = 1;
	size_t Np = 10000;
	string fileName("factorize.txt");

	// parse command line arguments
	for(int arg = 1; arg < argc; arg++) {
		string tmp(argv[arg]);

		if(tmp == string("-N")) {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> N;
			parameters.N = N;
		} else if(tmp == string("-Na")) {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> parameters.Na;
		} else if(tmp == string("-Nc")) {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> parameters.Nc;
		} else if(tmp == string("-Fc")) {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> parameters.Fc;
		} else if(tmp == string("-t")) {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> numThreads;
		} else if(tmp == string("-r")) {
			if(argc == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			stringstream(argv[arg]) >> repetitions;
		} else if(tmp == string("-o")) {
			if(arg == argc-1) {
				usage();
				return EXIT_FAILURE;
			}
			arg++;
			fileName = string(argv[arg]);
		} else if(tmp == string("--help")) {
			usage();
			return EXIT_FAILURE;
		} else {
			cerr << "Unknown argument \"" << tmp << "\"!" << endl << endl;;
			usage();
			return EXIT_FAILURE;
		}
	}

	vector<size_t> factors;
	stack<size_t> todo;

	cout << "Generating " << Np << " primes ...";
	vector<size_t> primes;
	sieveOfEratosthenes(primes, Np);
	cout << endl << endl;

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
	chrono::high_resolution_clock clk;
	for(size_t i = 0; i < repetitions; i++) {
		cout << "=====================" << endl;
		cout << " Run " << i+1 << "/" << repetitions << ":" << endl;
		cout << "=====================" << endl;

		size_t usedSteps = 0;
		chrono::high_resolution_clock::time_point start = clk.now();

		todo = stack<size_t>();
		factors.clear();

		// factor out primes
		/*for(size_t j = 0; j < primes.size(); j++) {
			while(N % primes[j] == 0) {
				factors.push_back(primes[j]);
				N /= primes[j];
			}
		}*/

		todo.push(N);

		while(!todo.empty()) {
			parameters.N = todo.top();
			if(parameters.N == 1) {
				todo.pop();
				continue;
			}
			if(binary_search(primes.begin(), primes.end(), parameters.N)) {
				todo.pop();
				factors.push_back(parameters.N);
				continue;
			}
			cout << "Factoring: " << parameters.N << endl;
			parameters.kB = guessBoltzmann(parameters.N);

			// TODO: add miller rabin

			PrimefacResult result = numThreads > 1 ? factorize(parameters, numThreads) : factorize(parameters);
			if(numThreads > 1) {
				PrimefacThread::reset();
			}
			if(result.success) {
				todo.pop();
				todo.push(result.factors.first);
				cout << todo.top() << " ";
				todo.push(result.factors.second);
				cout << endl;
			}

			usedSteps += result.usedSteps;
		}

		chrono::high_resolution_clock::time_point stop = clk.now();
		chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(stop-start);

		file << i << " ";

		cout << "Factors: ";
		size_t prod = 1;
		for(size_t j = 0; j < factors.size(); j++) {
			cout << factors[j] << ", ";
			prod *= factors[j];
		}
		if(prod == N) {
			file << 1 << " ";
			cout << "Success!" << endl;
		} else {
			file << 0 << " ";
			cout << "Failure!" << endl;
		}
		cout << "Duration: " << duration.count() << endl;
		file << duration.count() << " " << usedSteps << endl;

		cout << endl;
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
	cout << "  -Na [value]  Number of annealing steps"  << endl;
	cout << "  -Nc [value]  Number of conifgurations per annealing step" << endl;
	cout << "  -Fc [value]  Cooling factor per annealing step" << endl;
	cout << "  -t [value]   Number of threads" << endl;
	cout << "  -r [value]   Number of repetitions" << endl;
	cout << "  -o [file]    File the results will be written to" << endl;
}
