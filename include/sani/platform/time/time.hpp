#pragma once

#include "sani/types.hpp"

#include <chrono>
#include <ctime>

namespace sani {

	typedef std::chrono::high_resolution_clock				Clock;

	typedef std::chrono::high_resolution_clock::time_point	Time;

	/*
		TODO: inline?
	*/

	float32 toHours(const Time& time);

	float32 toMinutes(const Time& time);

	float32 toSeconds(const Time& time);

	float32 toMilliseconds(const Time& time);
}