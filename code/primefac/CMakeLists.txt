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
	primefac.cpp bitset
)

add_executable(
	primefac_mt
	primefac_mt.cpp bitset threading seed
)

add_executable(
	semiprime
	semiprime.cpp bitset
)

add_executable(
	semiprime_mt
	semiprime_mt.cpp bitset threading seed
)

add_executable(
	primelist
	primelist.cpp sieve
)

add_custom_command(
	OUTPUT ram-primes.sh
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/ram-primes.sh ${CMAKE_CURRENT_BINARY_DIR}/ram-primes.sh
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/ram-primes.sh
)
