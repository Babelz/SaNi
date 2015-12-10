#include "sani/engine/messaging/state_message.hpp"

namespace sani {

	namespace engine {

		StateMessage::StateMessage(const ServiceState newState, const ServiceState oldState) : newState(newState),
																							   oldState(oldState),
																							   handled(false) {
		}

		StateMessage::~StateMessage() {
		}
	}
}