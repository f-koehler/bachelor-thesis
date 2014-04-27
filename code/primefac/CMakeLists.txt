cmake_minimum_required (VERSION 2.6)
project(primefac)

#set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11 -g")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11 -march=native -O2")

add_executable(
	primefac
	main.cpp bitset.hpp bitset.cpp seed.hpp seed.cpp workerthread.hpp
)
