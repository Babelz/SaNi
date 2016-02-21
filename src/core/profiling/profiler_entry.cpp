#include "sani/core/profiling/profiler_entry.hpp"
#include "sani/platform/time/time.hpp"

namespace sani {
	ProfilerEntry::ProfilerEntry() : samplesCount(0) {
	}
	
	Time ProfilerEntry::getAverageTime() const {
		Duration duration;

		for (auto sample : samples) duration += sample.getElapsedTime().time_since_epoch();
		
		return Time(duration / MaxSamples);
	}

	void ProfilerEntry::beginMeasure() {
		samples[samplesCount].beginMeasure();
	}
	void ProfilerEntry::endMeasure() {
		samples[samplesCount].endMeasure();
		
		samplesCount++;

		if (samplesCount >= MaxSamples) samplesCount = 0;
	}
}