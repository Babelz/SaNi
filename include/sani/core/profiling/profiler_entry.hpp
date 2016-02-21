#pragma endregion

#include "sani/core/profiling/profiler_sample.hpp"
#include "sani/types.hpp"

namespace sani {

	const uint32 MaxSamples = 60;

	class ProfilerEntry final {
	private:
		ProfilerSample samples[MaxSamples];
		uint32 samplesCount;

		const String functionName;
	public:
		ProfilerEntry(const String& functionName);

		const String& getFunctionName() const;
		Time getAverageTime() const;

		~ProfilerEntry() = default;
	};
}