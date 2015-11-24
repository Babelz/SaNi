#pragma once

#include "sani/types.hpp"

#include <chrono>
#include <ctime>

namespace sani {
	/*
		TODO: check this, "sick" code.
	*/

	using Clock = std::chrono::high_resolution_clock;

	template<typename T>
	using Time = std::chrono::time_point<T>;

	/*
		Nanos
	*/

	template<typename T>
	uint64 nanoseconds(const Time<T>& time);

	template<typename T>
	float64 totalNanoseconds(const Time<T>& time);

	/*
		Micros
	*/

	template<typename T>
	uint64 microseconds(const Time<T>& time);

	template<typename T>
	float64 totalMicroseconds(const Time<T>& time);

	/*
		Millis
	*/

	template<typename T>
	uint64 milliseconds(const Time<T>& time);

	template<typename T>
	float64 totalMilliseconds(const Time<T>& time);

	/*
		Seconds
	*/

	template<typename T>
	uint64 seconds(const Time<T>& time);

	template<typename T>
	float64 totalSeconds(const Time<T>& time);

	/*
		Minutes
	*/

	template<typename T>
	uint64 minutes(const Time<T>& time);

	template<typename T>
	float64 totalMinutes(const Time<T>& time);

	/*
		Hours.
	*/

	template<typename T>
	uint64 hours(const Time<T>& time);

	template<typename T>
	float64 totalHours(const Time<T>& time);
}

#include "sani/platform/time/impl/time.hpp"