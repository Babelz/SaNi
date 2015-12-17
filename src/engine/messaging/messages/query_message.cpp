#include "sani/engine/messaging/messages/query_message.hpp"

namespace sani {
	
	namespace engine {
		
		namespace messages {
			QueryMessage::QueryMessage() : Message(MessageType::Query) {
			}

			void QueryMessage::setContents(const String& contents);
			const String& QueryMessage::getContents() const;

			void QueryMessage::setCommand(const uint32 command);
			uint32 QueryMessage::getCommand() const;

			void QueryMessage::setResults(void* const results);
			void* QueryMessage::getResults();
			
			bool QueryMessage::success() const;
		}
	}
}