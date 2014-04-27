CXX=g++
CXXFLAGS=-x c++ -std=c++11 -Wall -Wextra -pedantic -g
#CXXFLAGS=-x c++ -std=c++11 -Wall -Wextra -pedantic -O2 -march=native

INC=bitset.hpp seed.hpp
SRC=main.cpp bitset.cpp seed.cpp

all: primefac
primefac: Makefile $(INC) $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

.PHONY: clean
clean:
	rm -f primefac
