#pragma once

namespace sani {

	namespace engine {

		enum class ServiceState {
			/// Service has not been initialized yet.
			Uninitialized,
			
			/// Service is being suspended for a given amount of time.
			Suspended,
			
			/// Service has been terminated and it should be disposed.
			Terminated,

			/// Service is running.
			Running
		};
	}
}