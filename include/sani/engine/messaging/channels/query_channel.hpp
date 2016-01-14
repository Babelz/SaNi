#pragma once	

#include "sani/engine/messaging/channels/peer_to_peer_channel.hpp"
#include "sani/engine/messaging/messages/query_message.hpp"

namespace sani {

	namespace engine {
		
		namespace channels {

			class QueryChannel final : public PeerToPeerChannel<messages::QueryMessage> {
			public: 
				QueryChannel(ServiceRegistry* const serviceRegistry);
			};
		}
	}
}