#pragma once

#include "sani/platform/time/time.hpp"

namespace sani {

	/// @class EngineTime engine_time.hpp "sani/platform/time/engine_time.hpp"
	/// @author voidbab
	///
	/// Contains various time variables used to update the engine,
	/// such as total time and frame time.
	class EngineTime {
	private:
		/*
			TODO: do we need anything else?
		*/

		/// Total time elapsed.
		const float64 totalTime;
		/// Current frametime.
		const float64 frameTime;
	public:

		EngineTime(const float64 totalTime, const float64 frameTime);

		float64 getTotalTime() const;
		float64 getFrameTime() const;
		
		~EngineTime();
	};
}