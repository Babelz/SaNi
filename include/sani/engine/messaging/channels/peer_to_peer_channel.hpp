#pragma once

#include "sani/engine/messaging/channels/channel.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, Message);

namespace sani {

	namespace engine {
		
		namespace channels {

			/// @class PeerToPeerChannel peer_to_peer_channel.hpp "sani/engine/messaging/channels/peer_to_peer_channel.hpp"
			/// @author voidbab
			///
			/// Simple peer to peer channel.
			class PeerToPeerChannel : public Channel {
			public:
				PeerToPeerChannel(ServiceRegistry* const serviceRegistry);

				/// Routes the next message.
				void flush() override;

				/// Creates new empty p2p message.
				messages::Message* const createEmptyMessage() override;
				/// Releases (aka recycles) a given p2p message element.
				void releaseMessage(messages::Message* const message) override;
			};
		}
	}
}