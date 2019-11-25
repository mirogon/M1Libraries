#pragma once
#include <time.h>
#include <stdlib.h>
#include <random>

namespace m1 {
	class Random {

	public:

		//Random class constructor
		Random();

		//Random class deconstructor
		virtual ~Random() = default;

		//Return a random number from min to max
		int random_number(long min, long max);

	private:

		std::random_device rd;
		std::mt19937 mt;

	};

	inline Random::Random()
	{
		mt.seed(rd());
	}

	inline int Random::random_number(long min, long max) {

		std::uniform_int_distribution<uint32_t> uint_dist(min, max);
		return uint_dist(mt);
	}

}