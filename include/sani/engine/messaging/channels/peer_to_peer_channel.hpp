#pragma once

#include "sani/engine/messaging/messages/peer_to_peer_message.hpp"
#include "sani/engine/messaging/channels/channel.hpp"
#include "sani/core/memory/page_pool_allocator.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, Message);

namespace sani {

	namespace engine {
		
		namespace channels {

			/// @class PeerToPeerChannel peer_to_peer_channel.hpp "sani/engine/messaging/channels/peer_to_peer_channel.hpp"
			/// @author voidbab
			///
			/// Simple peer to peer channel.
			template <typename T>
			class PeerToPeerChannel final : public Channel {
			private:
				PagePoolAllocator<T> messagePool;
			public:
				PeerToPeerChannel(ServiceRegistry* const serviceRegistry, const MessageType type);

				/// Routes the next message.
				void flush() final override;

				/// Creates new empty p2p message.
				messages::Message* const createEmptyMessage() final override;
				/// Releases (aka recycles) a given p2p message.
				void releaseMessage(messages::Message* const message) final override;
			};
		}
	}
}

#include "sani/engine/messaging/channels/impl/peer_to_peer_channel.hpp"