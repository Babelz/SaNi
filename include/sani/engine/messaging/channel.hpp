#pragma once

#include "sani/engine/messaging/message_type.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <queue>

SANI_FORWARD_DECLARE_2(sani, engine, ServiceRegistry);
SANI_FORWARD_DECLARE_2(sani, engine, Message);

namespace sani {

	namespace engine {
		
		/// @class Channel channel.hpp "sani/engine/messaging/channel.hpp"
		/// @author voidbab
		///
		/// Represents a messaging channel that the consumers
		/// and services can use to send messages.
		class Channel {
		private:
			std::queue<Message* const> messageQueue;

			ServiceRegistry* const serviceRegistry;
			
			// Defines the types of messages that this channel will accept.
			const MessageType channelType;
		protected:
			ServiceRegistry* const getServiceRegistry();

			/// Adds the given message to the channels internal
			/// message queue for later processing.
			void queueMessage(Message* const message);

			/// Returns the next message from the internal message queue.
			Message* const nextMessage();
		public:
			Channel(const MessageType channelType, ServiceRegistry* const serviceRegistry);

			/// Returns true if the channel contains 
			/// messages that are yet to be routed.
			bool empty() const;
			
			/// Routes the next message.
			virtual void flush() = 0;

			/// Routes the given message to all the
			/// recipents who should know about it.
			void route(Message* const message);

			virtual ~Channel();
		};
	}
}