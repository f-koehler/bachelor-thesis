cmake_minimum_required (VERSION 2.8)
project(primefac)

add_custom_target(Profile)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11 -march=native -O2 -pthread")
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++11 -g -pthread")

add_library(
	bitset
	OBJECT
	bitset.cpp bitset.hpp config.hpp
)

add_library(
	seed
	OBJECT
	seed.cpp seed.hpp config.hpp
)

add_library(
	threading
	OBJECT
	threading.cpp threading.hpp config.hpp
)

add_library(
	sieve
	OBJECT
	sieve.cpp sieve.hpp config.hpp
)

add_executable(
	primefac
	main_primefac.cpp config.hpp bitset threading seed primefac
)

add_executable(
	semiprime
	main_semiprime.cpp config.hpp bitset threading seed primefac
)

add_executable(
	primelist
	primelist.cpp config.hpp sieve
)

add_executable(
	prngbench
	prngbench.cpp config.hpp
)

find_package(MPI)
if(MPI_FOUND)
	add_custom_target(mpi)
endif(MPI_FOUND)

# a target to build the documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)
