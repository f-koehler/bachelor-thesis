#ifndef THREADING_HPP_
#define THREADING_HPP_

#include "config.hpp"
#include "bitset.hpp"
#include "seed.hpp"
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <utility>
#include <cmath>

namespace primefac
{

	/** @brief This is a threading class to factorize numbers */
	class PrimefacThread
	{
		public:
			/** A struct that holds the configuration for a primefac thread */
			typedef struct {
				/** N, the number to factorize */
				std::size_t number;

				/** Nc, the number of configurations per annealing step */
				std::size_t numConfigurations;

				/** Na, the number of annealing steps */
				std::size_t numAnnealingSteps;

				/** Fc, the cooling factor */
				double coolingFactor;

				/** kB, the Boltzmann constant */
				double kB = 0.0;


				/** The ID of the corresponding thread */
				std::size_t threadId;

				/** The number of threads to use */
				std::size_t numThreads;
			} Configuration;

		private:
			static bool success;
			static std::vector<std::size_t> factors;

			/** The C++11 instance for the computing */
			std::thread thr;
	
		
			static std::atomic_bool   completed;
			static std::atomic_size_t numSearched;

			void threadFunc(const Configuration& config);

		public:
			PrimefacThread(Configuration& config);

			/**
			 * Join the thread.
			 */
			void join();

			static bool getSuccess();
			static std::vector<std::size_t> getFactors();
			
			/**
			 * This function will create a set of primefac thread configurations.
			 * @param[in] number The number to factorize
			 * @param[in] numConfigurations The number of configurations per annealing steps
			 * @param[in] numAnnealingSteps The number of annealing steps
			 * @param[in] coolingFactor The cooling factor for the annealing process
			 * @param[in] kB The value for the Boltzmann constant
			 * @param[in] numThreads The number og threads to use
			 * @return A vector holding the configurations.
			 */
			static std::vector<PrimefacThread::Configuration> createConfigurations(
					std::size_t number, std::size_t numConfigurations,
					std::size_t numAnnealingSteps, double coolingFactor, 
					double kB, std::size_t numThreads);
	};


	/** @brief This is a threading class to factorize semiprime numbers */
	class SemiprimeThread
	{
		public:
			/** A struct that holds the configuration for a semiprime thread */
			typedef struct {
				/** The first factor of the semiprime number */
				std::size_t prime1;

				/** The second factor of the semiprime number */
				std::size_t prime2;

				/** Nc, the number of configurations per annealing step */
				std::size_t numConfigurations;

				/** Na, the number of annealing steps */
				std::size_t numAnnealingSteps;

				/** Fc, the cooling factor */
				double coolingFactor;

				/** kB, the Boltzmann constant */
				double kB = 0.0;


				/** The ID of the corresponding thread */
				std::size_t threadId;

				/** The number of threads to use */
				std::size_t numThreads;
			} Configuration;

		private:
			static bool success;
			static std::pair<std::size_t, std::size_t> factors;

			/** The C++11 instance for the computing */
			std::thread thr;

			static std::atomic_bool   completed;
			static std::atomic_size_t numSearched;

			void threadFunc(const Configuration& config);

		public:
			SemiprimeThread(Configuration& config);

			/*
			 * Join the thread.
			 */
			void join();

			static bool getSuccess();
			static std::pair<std::size_t, std::size_t> getFactors();

			/**
			 * This function will create a set of semiprime thread configurations.
			 * @param[in] prime1 The first prime factor of the semiprime number
			 * @param[in] prime2 The second prime factor of the semiprime number
			 * @param[in] numConfigurations The number of configurations per annealing steps
			 * @param[in] numAnnealingSteps The number of annealing steps
			 * @param[in] coolingFactor The cooling factor for the annealing process
			 * @param[in] kB The value for the Boltzmann constant
			 * @param[in] numThreads The number og threads to use
			 * @return A vector holding the configurations.
			 */
			static std::vector<Configuration> createConfigurations(
					std::size_t prime1, std::size_t prime2,
					std::size_t numConfigurations, std::size_t numAnnealingSteps,
					double coolingFactor, double kB, std::size_t numThreads);
	};
}

#endif
