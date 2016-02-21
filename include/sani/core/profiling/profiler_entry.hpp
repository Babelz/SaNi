#pragma endregion

#include "sani/core/profiling/profiler_sample.hpp"
#include "sani/types.hpp"

namespace sani {

	const uint32 MaxSamples = 64;

	/// @class ProfilerEntry profiler_entry.hpp "sani/core/profiling/profiler_entry.hpp"
	/// @author voidbab
	/// 
	/// Profiler entry that contains given count of samples.
	/// Used by the profiler module.
	class ProfilerEntry final {
	private:
		// Ring buffer container to keep track of the samples.
		ProfilerSample samples[MaxSamples];
		
		uint32 samplesCount;
	public:
		ProfilerEntry();

		/// Returns the average time from 
		/// measured samples.
		float32 averageMicroSeconds() const;

		/// Begins measuring new sample.
		void beginMeasure();
		/// Ends measuring.
		void endMeasure();

		~ProfilerEntry() = default;
	};
}