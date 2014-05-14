CXX=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11 -O2 -march=native -pthread

SRC=$(wildcard *.cpp)
INC=$(wildcard *.hpp)
OBJ=$(patsubst %.cpp,obj/%.o,$(SRC))
EXECUTABLES=factorize semiprime onestep prngbench primelist
BIN=$(patsubst %,bin/%,$(EXECUTABLES))

all: $(BIN)
obj/bitset.o: bitset.cpp bitset.hpp config.hpp
	$(CXX) $(CFLAGS) -c $< -o $@
obj/guess.o: guess.cpp guess.hpp config.hpp
	$(CXX) $(CFLAGS) -c $< -o $@
obj/primefac.o: primefac.cpp primefac.hpp config.hpp
	$(CXX) $(CFLAGS) -c $< -o $@
obj/seed.o: seed.cpp seed.hpp config.hpp
	$(CXX) $(CFLAGS) -c $< -o $@
obj/sieve.o: sieve.cpp sieve.hpp config.hpp
	$(CXX) $(CFLAGS) -c $< -o $@
obj/threading.o: threading.cpp threading.hpp config.hpp
	$(CXX) $(CFLAGS) -c $< -o $@
obj/main_factorize.o: main_factorize.cpp config.hpp
	$(CXX) $(CFLAGS) -c $< -o $@
obj/main_onestep.o: main_onestep.cpp config.hpp
	$(CXX) $(CFLAGS) -c $< -o $@
obj/main_semiprime.o: main_semiprime.cpp config.hpp
	$(CXX) $(CFLAGS) -c $< -o $@
obj/main_prngbench.o: main_prngbench.cpp config.hpp
	$(CXX) $(CFLAGS) -c $< -o $@
obj/main_primelist.o: main_primelist.cpp config.hpp
	$(CXX) $(CFLAGS) -c $< -o $@
bin/factorize: obj/main_factorize.o obj/primefac.o obj/bitset.o obj/threading.o obj/seed.o obj/sieve.o obj/guess.o
	$(CXX) $(CFLAGS) $^ -o $@
bin/semiprime: obj/main_semiprime.o obj/primefac.o obj/bitset.o obj/threading.o obj/seed.o obj/guess.o
	$(CXX) $(CFLAGS) $^ -o $@
bin/onestep: obj/main_onestep.o obj/primefac.o obj/bitset.o obj/threading.o obj/seed.o obj/guess.o
	$(CXX) $(CFLAGS) $^ -o $@
bin/prngbench: obj/main_prngbench.o
	$(CXX) $(CFLAGS) $^ -o $@
bin/primelist: obj/main_primelist.o obj/sieve.o
	$(CXX) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf obj/* bin/*
