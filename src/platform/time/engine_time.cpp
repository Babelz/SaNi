#include "sani/platform/time/engine_time.hpp"

namespace sani {

	EngineTime::EngineTime(const float64 totalTime, const float64 frameTime) : totalTime(totalTime),
																			   frameTime(frameTime) {
	}

	float64 EngineTime::getTotalTime() const {
		return totalTime;
	}
	float64 EngineTime::getFrameTime() const {
		return frameTime;
	}

	EngineTime::~EngineTime() {
	}
}