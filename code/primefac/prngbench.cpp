#include "config.hpp"
#include <iostream>
#include <chrono>
#include <random>
using namespace std;
using namespace chrono;

typedef time_point<high_resolution_clock> Time;

int main()
{
	size_t N = 1e8;
	size_t i = 0;

	// create the engines
	default_random_engine engineDefault;
	minstd_rand           engineMinstdRand;
	minstd_rand0          engineMinstdRand0;
	mt19937               engineMt19937;
	mt19937_64            engineMt19937_64;
	ranlux24_base         engineRanlux24Base;
	ranlux48_base         engineRanlux48Base;
	ranlux24              engineRanlux24;
	ranlux48              engineRanlux48;
	knuth_b               engineKnuthB;

	// distributions
	uniform_int_distribution<size_t>  intDist(0, 1);

	high_resolution_clock clock;
	Time start;
	Time stop;

	// seed all engines with the same seed
	engineDefault.seed(42);
	engineMinstdRand.seed(42);
	engineMinstdRand0.seed(42);
	engineMt19937.seed(42);
	engineMt19937_64.seed(42);
	engineRanlux24Base.seed(42);
	engineRanlux48Base.seed(42);
	engineRanlux24.seed(42);
	engineRanlux48.seed(42);
	engineKnuthB.seed(42);

	cout << "Uniform int distribution for std::size_t on (0,1):" << endl;
	cout << "default_random_engine: ";
	start = clock.now();
	for(i = 0; i < N; i++) {
		intDist(engineDefault);
	}
	stop = clock.now();
	cout << duration_cast<nanoseconds>(stop - start).count() << " ns" << endl;
	
	cout << "mindst_rand:           ";
	start = clock.now();
	for(i = 0; i < N; i++) {
		intDist(engineMinstdRand);
	}
	stop = clock.now();
	cout << duration_cast<nanoseconds>(stop - start).count() << " ns" << endl;

	cout << "mindst_rand0:          ";
	start = clock.now();
	for(i = 0; i < N; i++) {
		intDist(engineMinstdRand0);
	}
	stop = clock.now();
	cout << duration_cast<nanoseconds>(stop - start).count() << " ns" << endl;

	cout << "mt19937:               ";
	start = clock.now();
	for(i = 0; i < N; i++) {
		intDist(engineMt19937);
	}
	stop = clock.now();
	cout << duration_cast<nanoseconds>(stop - start).count() << " ns" << endl;

	cout << "mt19937_64:            ";
	start = clock.now();
	for(i = 0; i < N; i++) {
		intDist(engineMt19937_64);
	}
	stop = clock.now();
	cout << duration_cast<nanoseconds>(stop - start).count() << " ns" << endl;

	cout << "ranlux24_base:         ";
	start = clock.now();
	for(i = 0; i < N; i++) {
		intDist(engineRanlux24Base);
	}
	stop = clock.now();
	cout << duration_cast<nanoseconds>(stop - start).count() << " ns" << endl;

	cout << "ranlux48_base:         ";
	start = clock.now();
	for(i = 0; i < N; i++) {
		intDist(engineRanlux48Base);
	}
	stop = clock.now();
	cout << duration_cast<nanoseconds>(stop - start).count() << " ns" << endl;

	cout << "ranlux24:              ";
	start = clock.now();
	for(i = 0; i < N; i++) {
		intDist(engineRanlux24);
	}
	stop = clock.now();
	cout << duration_cast<nanoseconds>(stop - start).count() << " ns" << endl;

	cout << "ranlux48:              ";
	start = clock.now();
	for(i = 0; i < N; i++) {
		intDist(engineRanlux48);
	}
	stop = clock.now();
	cout << duration_cast<nanoseconds>(stop - start).count() << " ns" << endl;

	cout << "knuth_b:               ";
	start = clock.now();
	for(i = 0; i < N; i++) {
		intDist(engineKnuthB);
	}
	stop = clock.now();
	cout << duration_cast<nanoseconds>(stop - start).count() << " ns" << endl;

	return EXIT_SUCCESS;
}
