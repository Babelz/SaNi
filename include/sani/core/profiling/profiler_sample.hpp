#pragma once

#include "sani/platform/time/time.hpp"
#include "sani/types.hpp"

namespace sani {

	/// @class ProfilerSample profiler_sample.hpp "sani/core/profiling/profiler_sample.hpp"
	/// @author voidbab
	/// 
	/// One time measurement of some given procedure.
	class ProfilerSample final {
	private:
		Time begin;
		Time end;
	public:
		ProfilerSample();

		/// Returns the elapsed time.
		float32 elapsedMicroSeconds() const;

		/// Starts measuring procedure time.
		void beginMeasure();
		/// Ends measuring the procedure time.
		void endMeasure();

		~ProfilerSample() = default;
	};
}