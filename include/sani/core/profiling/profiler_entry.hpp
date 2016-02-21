#pragma endregion

#include "sani/core/profiling/profiler_sample.hpp"
#include "sani/types.hpp"

#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_1(sani, ProfilerModule);

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

		Time getAverageTime() const;

		~ProfilerEntry() = default;
	};
}