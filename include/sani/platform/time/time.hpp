#pragma once

#include "sani/types.hpp"

#include <chrono>
#include <ctime>

namespace sani {

	using Clock		= std::chrono::high_resolution_clock;
	using Time		= std::chrono::high_resolution_clock::time_point;
	using Duration	= std::chrono::high_resolution_clock::duration;

	float32 toHours(const Time& time);

	float32 toMinutes(const Time& time);

	float32 toSeconds(const Time& time);

	float32 toMilliseconds(const Time& time);

	float32 toMicroSeconds(const Time& time);
}