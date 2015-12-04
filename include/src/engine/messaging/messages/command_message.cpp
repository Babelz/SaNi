#include "sani/engine/messaging/messages/command_message.hpp"

namespace sani {

	namespace engine {
		
		namespace messages {

			CommandMessage::CommandMessage(const uint32 command, const String& data) : Message(MessageType::Command), 
																					   command(command),
																					   data(data) {
			}
			CommandMessage::CommandMessage(const uint32 command) : CommandMessage(command, String()) {
			}
			CommandMessage::CommandMessage() : CommandMessage(0, String()) {
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