cmake_minimum_required (VERSION 2.8)
project(primefac)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11 -g -pthread")
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11 -march=native -O2 -pthread")

add_library(
	bitset
	OBJECT
	bitset.cpp bitset.hpp
)

add_library(
	seed
	OBJECT
	seed.cpp seed.hpp
)

add_library(
	threading
	OBJECT
	threading.cpp threading.hpp
)

add_library(
	sieve
	OBJECT
	sieve.cpp sieve.hpp
)

add_executable(
	primefac
	main.cpp bitset
)

add_executable(
	semiprime
	semiprime.cpp bitset
)

add_executable(
	primefac_mt
	main_mt.cpp bitset threading
)

add_executable(
	primelist
	primelist.cpp sieve
)
