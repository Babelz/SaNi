#pragma once	

#include "sani/engine/messaging/recipient_list.hpp"
#include "sani/engine/messaging/message_type.hpp"

namespace sani {

	namespace engine {

		namespace messages {

			/// @class Message message.hpp "sani/engine/messaging/message.hpp
			/// @author voidbab
			///
			/// Serves as a base class for all other messages.
			/// Represents a message that the services and consumers and use
			/// to message each other. 
			class Message {
			private:
				// Type of the message.
				const MessageType type;

				// Recipients of the message.
				RecipientList recipients;

				// Was this message handled by the recipients.
				bool handled;
			public:
				Message(const MessageType type);

				/// Returns true if this message was handled.
				bool wasHandled() const;
				/// Marks this message as handled.
				void markUnhandled();
				/// Marks this message as unhandled aka resets it's state.
				void markHandled();

				/// Returns the recipient list of this message.
				RecipientList& getRecipients();
				/// Returns the type of this message.
				MessageType getType() const;

				virtual ~Message();

				Message(Message& other) = delete;
				Message(Message&& other) = delete;

				Message& operator =(Message& other) = delete;
				Message& operator =(Message&& other) = delete;
			};
		}
	}
}