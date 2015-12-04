#pragma once

#include "sani/engine/messaging/messages/message.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace engine {
		
		namespace messages {

			/// @class CommandMessage command_message.hpp "sani/engine/messaging/command_message.hpp"
			/// @author voidbab
			///
			/// Message that delegates a method/function call to 
			/// the recipient(s).
			class CommandMessage final : public Message {
			private:
				// Command related to this message.
				// Recipients use this to interpret 
				// the contained value as some function/method
				// call.
				uint32 command;

				// Additional command data.
				// Can be empty.
				String data;
			public:
				CommandMessage(const uint32 command, const String& data);
				CommandMessage(const uint32 command);
				CommandMessage();

				/// Returns the messages data to the caller.
				const String& getData() const;
				/// Sets the messages optional data contents.
				void setData(const String& data);

				/// Returns the messages command.
				uint32 getCommand() const;
				/// Sets the messages command.
				void setCommand(const uint32 command);
			};
		}
	}
}