#pragma once

#include "sani/types.hpp"

#include <chrono>
#include <ctime>

namespace sani {
	typedef std::chrono::high_resolution_clock				Clock;

	typedef std::chrono::high_resolution_clock::time_point	Time;
}