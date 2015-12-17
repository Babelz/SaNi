#pragma once

#include "sani/engine/messaging/messages/message.hpp"

namespace sani {

	namespace engine {
		
		namespace messages {

			/// @class QueryMessage query_message.hpp "sani/engine/messaging/query_message.hpp"
			/// @author voidbab
			///
			/// Message that merges command and document functionalities 
			/// inside a single message. Query messages are used with 
			/// specialized operations that require a given command, 
			/// some input for it and return data back to the user.
			class QueryMessage : public Message {
			private:
				String contents;
				uint32 command;
				
				void* results;
			public:
				QueryMessage();

				/// Returns the message contents to the caller.
				void setContents(const String& contents);
				/// Sets the message contents.
				const String& getContents() const;

				/// Sets the command.
				void setCommand(const uint32 command);
				/// Returns the command to the caller.
				uint32 getCommand() const;

				/// Sets result data.
				void setResults(void* const results);
				/// Returns the results to the caller.
				void* getResults();

				/// Returns true if the message contains result data.
				bool success() const;
			};
		}
	}
}