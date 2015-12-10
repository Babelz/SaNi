#pragma once

#include "sani/engine/service_state.hpp"

namespace sani {

	namespace engine {
		
		class StateMessage {
		public:
			// New state of the service.
			const ServiceState newState;
			// Old state of the service.
			const ServiceState oldState;

			// Did the service handle this message successfully.
			bool handled;

			StateMessage(const ServiceState newState, const ServiceState oldState);
			
			~StateMessage();
		};
	}
}