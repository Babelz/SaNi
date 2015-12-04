#pragma once	

#include "sani/engine/messaging/recipent_list.hpp"
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
			public:
				// Type of the message.
				const MessageType type;

				// Recipents of the message.
				RecipentList recipents;

				// Was this message handled by the recipent.
				bool handled;

				Message(const MessageType type);

				virtual ~Message();
			};
		}
	}
}