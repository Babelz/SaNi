#include "sani/core/profiling/profiler_module.hpp"

namespace sani {

	float32 ProfilerModule::elapsedMicroSeconds() const {
		float32 elapsed = 0.0f;

		for (auto entry : entries) elapsed += entry.second.averageMicroSeconds();
		
		return elapsed;
	}

	void ProfilerModule::beginProfiling(const String& function) {
		if (entries.count(function) == 0) entries[function] = ProfilerEntry();

		entries[function].beginMeasure();
	}
	void ProfilerModule::endProfiling(const String& function) {
		entries[function].endMeasure();
	}

	ProfilerEntriesIterator ProfilerModule::begin() {
		return entries.begin();
	}
	ProfilerEntriesIterator ProfilerModule::end() {
		return entries.end();
	}
}