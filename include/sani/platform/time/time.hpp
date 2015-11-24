#pragma once

#include "sani/types.hpp"

#include <chrono>
#include <ctime>

namespace sani {
	typedef std::chrono::high_resolution_clock Clock;

	template<typename T>
	using Time = std::chrono::time_point<T, std::chrono::high_resolution_clock>;
}