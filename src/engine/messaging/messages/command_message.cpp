#include "sani/engine/messaging/messages/command_message.hpp"

namespace sani {

	namespace engine {
		
		namespace messages {

			CommandMessage::CommandMessage() : Message(MessageType::Command),
											   command(0) {
			}

			const String& CommandMessage::getData() const {
				return data;
			}
			void CommandMessage::setData(const String& data) {
				this->data = data;
			}

			uint32 CommandMessage::getCommand() const {
				return command;
			}
			void CommandMessage::setCommand(const uint32 command) {
				this->command = command;
			}
		}
	}
}