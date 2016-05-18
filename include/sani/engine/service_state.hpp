#pragma once

#include "sani/types.hpp"

namespace sani {

	namespace engine {

		enum class ServiceState : int32 {
			/// Service has not been initialized yet.
			Uninitialized = 0,
			
			/// Service is being suspended for a given amount of time.
			Suspended,
			
			/// Service has been terminated and it should be disposed.
			Terminated,

			/// Service is running.
			Running
		};
	}
}