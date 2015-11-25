#pragma once

namespace sani {

	namespace engine {

		enum class ServiceState {
			/// Service has not been initialized yet.
			Uninitialized,
			/// Service is being suspended for a given amount of time.
			Suspended,
			/// Service is stopped and it should be disposed.
			Stopped,
			/// Service is running.
			Running
		};
	}
}