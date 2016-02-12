#include "sani/platform/time/time.hpp"

namespace sani {

	float32 toHours(const Time& time) {
		return static_cast<float32>(std::chrono::duration_cast<std::chrono::hours>(time.time_since_epoch()).count());
	}

	float32 toMinutes(const Time& time) {
		return static_cast<float32>(std::chrono::duration_cast<std::chrono::minutes>(time.time_since_epoch()).count());
	}

	float32 toSeconds(const Time& time) {
		return static_cast<float32>(std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count());
	}

	float32 toMilliseconds(const Time& time) {
		return static_cast<float32>(std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count());
	}

	float32 toMicroSeconds(const Time& time) {
		return static_cast<float32>(std::chrono::duration_cast<std::chrono::microseconds>(time.time_since_epoch()).count());
	}
}