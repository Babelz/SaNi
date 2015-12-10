#include "sani/engine/messaging/messages/message.hpp"

namespace sani {

	namespace engine {

		namespace messages {

			Message::Message(const MessageType type) : type(type),
													   handled(false) {
			}

			bool Message::wasHandled() const {
				return handled;
			}
			void Message::markUnhandled() {
				handled = false;
			}
			void Message::markHandled() {
				handled = true;
			}

			RecipientList& Message::getRecipents() {
				return recipents;
			}
			MessageType Message::getType() const {
				return type;
			}

			Message::~Message() {
			}
		}
	}
}