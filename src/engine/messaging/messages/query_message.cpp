#include "sani/engine/messaging/messages/query_message.hpp"

namespace sani {
	
	namespace engine {
		
		namespace messages {
			QueryMessage::QueryMessage() : Message(MessageType::Query),
										   results(nullptr) {
			}

			void QueryMessage::setContents(const String& contents) {
				this->contents = contents;
			}
			const String& QueryMessage::getContents() const {
				return contents;
			}

			void QueryMessage::setCommand(const uint32 command) {
				this->command = command;
			}
			uint32 QueryMessage::getCommand() const {
				return command;
			}

			void QueryMessage::setResults(void* const results) {
				this->results = results;
			}
			void* QueryMessage::getResults() {
				return results;
			}
			
			bool QueryMessage::success() const {
				return wasHandled() && results != nullptr;
			}
		}
	}
}