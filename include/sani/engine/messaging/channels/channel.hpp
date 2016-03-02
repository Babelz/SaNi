#pragma once

#include "sani/engine/messaging/message_releasing_strategy.hpp"
#include "sani/engine/messaging/message_type.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <queue>

SANI_FORWARD_DECLARE_3(sani, engine, messages, Message);
SANI_FORWARD_DECLARE_2(sani, engine, ServiceRegistry);

namespace sani {

	namespace engine {

		namespace channels {

			const uint32 MESSAGE_POOL_PAGE_SIZE		= 16;
			const uint32 MESSAGE_POOL_PAGES_COUNT	= 1;

			/// @class Channel channel.hpp "sani/engine/messaging/channel.hpp"
			/// @author voidbab
			///
			/// Represents a messaging channel that the consumers
			/// and services can use to send messages.
			class Channel {
			private:
				ServiceRegistry* const serviceRegistry;

				// Defines the types of messages that this channel will accept.
				const MessageType channelType;
				const messages::MessageReleaseStrategy messageReleaseStrategy;
			protected:
				messages::MessageReleaseStrategy getMessageReleaseStrategy() const;
				ServiceRegistry* const getServiceRegistry();

				Channel(const MessageType channelType, ServiceRegistry* const serviceRegistry, const messages::MessageReleaseStrategy messageReleaseStrategy);
				
				/// Routes the next message.
				virtual void routeMessage(messages::Message* const message) = 0;
			public:
				/// Returns the type of this channel.
				MessageType getType() const;

				/// Creates new empty message suited for this channel.
				virtual messages::Message* const createEmptyMessage() = 0;
				/// Releases (aka recycles) a given message element.
				virtual void releaseMessage(messages::Message* const message) = 0;

				/// Routes the given message to all the
				/// recipients who should know about it.
				void route(messages::Message* const message);

				virtual ~Channel();

				Channel(Channel& other) = delete;
				Channel(Channel&& other) = delete;

				Channel& operator =(Channel& other) = delete;
				Channel& operator =(Channel&& other) = delete;
			};
		}
	}
}