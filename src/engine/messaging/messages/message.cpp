#include "sani/engine/messaging/messages/message.hpp"

namespace sani {

	namespace engine {

		namespace messages {

			Message::Message(const MessageType type) : type(type),
				handled(false) {
			}

			Message::~Message() {
			}
		}
	}
}