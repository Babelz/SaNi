#pragma once

namespace sani {

	namespace engine {

		enum class ServiceState {
			/// Service is being suspended for a given amount of time.
			Suspended,
			/// Service is stopped.
			Stopped,
			/// Service is running.
			Running,
			/// Service is in invalid state and should not be used anymore.
			Invalid
		};
	}
}