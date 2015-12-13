#pragma once

#include "sani/engine/messaging/messages/document_message.hpp"

namespace sani {

	namespace engine {
		
		namespace messages {

			DocumentMessage::DocumentMessage() : Message(MessageType::Document),
												data(nullptr) {
			}

			void DocumentMessage::setCommand(const uint32 command) {
				this->command = command;
			}
			uint32 DocumentMessage::getCommand() const {
				return command;
			}

			void DocumentMessage::setData(void* const data) {
				this->data = data;
			}
			void* DocumentMessage::getData() {
				return data;
			}

			void DocumentMessage::clearData() {
				data = nullptr;
			}
		}
	}
}