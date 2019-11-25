#pragma once
#include <stdint.h>
#include <chrono>

namespace m1 {

	class Timer
	{
	public:

		Timer();
		~Timer() = default;

		void restart_timer();

		//Return the delta time in seconds
		uint64_t elapsed_time_sec();
		//Return the delta time in milliseconds
		uint64_t elapsed_time_milli();
		//Return the delta time in microseconds
		uint64_t elapsed_time_micro();
		//Return the delta time in nanoseconds
		uint64_t elapsed_time_nano();


	private:

		std::chrono::high_resolution_clock::time_point start_time;

	};

	inline Timer::Timer() :

		start_time{ std::chrono::high_resolution_clock::now() }

	{}

	inline void Timer::restart_timer()
	{
		start_time = std::chrono::high_resolution_clock::now();
	}
	inline uint64_t Timer::elapsed_time_sec()
	{
		return std::chrono::duration_cast<std::chrono::duration< uint64_t, std::ratio<1, 1> >>(std::chrono::high_resolution_clock::now() - start_time).count();
	}

	inline uint64_t Timer::elapsed_time_milli()
	{
		return std::chrono::duration_cast<std::chrono::duration< uint64_t, std::ratio<1, 1000> >>(std::chrono::high_resolution_clock::now() - start_time).count();
	}

	inline uint64_t Timer::elapsed_time_micro()
	{
		return std::chrono::duration_cast<std::chrono::duration< uint64_t, std::ratio<1, 1000000> >>(std::chrono::high_resolution_clock::now() - start_time).count();
	}
	inline uint64_t Timer::elapsed_time_nano()
	{
		return std::chrono::duration_cast<std::chrono::duration< uint64_t, std::ratio<1, 1000000000> >>(std::chrono::high_resolution_clock::now() - start_time).count();
	}
}

