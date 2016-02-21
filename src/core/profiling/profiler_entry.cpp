#include "sani/core/profiling/profiler_entry.hpp"
#include "sani/platform/time/time.hpp"

namespace sani {
	ProfilerEntry::ProfilerEntry() : samplesCount(0) {
	}
	
	float32 ProfilerEntry::averageMicroSeconds() const {
		float32 microSeconds = 0.0f;

		for (uint32 i = 0; i < MaxSamples; i++) microSeconds += samples[i].elapsedMicroSeconds();

		return microSeconds / MaxSamples;
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