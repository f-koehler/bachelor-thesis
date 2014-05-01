cmake_minimum_required (VERSION 2.6)
project(primefac)

#set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11 -g")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11 -march=native -O2")

add_executable(
	primefac
	main.cpp bitset.hpp bitset.cpp seed.hpp seed.cpp
)

add_executable(
	semiprime
	semiprime.cpp bitset.hpp bitset.cpp seed.hpp seed.cpp
)

add_executable(
	primefac_mt
	main_mt.cpp bitset.hpp bitset.cpp seed.hpp seed.cpp threading.hpp threading.cpp
)
