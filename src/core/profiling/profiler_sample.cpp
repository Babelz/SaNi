#include "sani/core/profiling/profiler_sample.hpp"

namespace sani {

	ProfilerSample::ProfilerSample() : begin(Clock::now()),
									   end(Clock::now()) {
	}

	Time ProfilerSample::getElapsedTime() const {
		return Time(end - begin);
	}

	void ProfilerSample::beginMeasure() {
		begin = Clock::now();
	}
	void ProfilerSample::endMeasure() {
		end = Clock::now();
	}
}