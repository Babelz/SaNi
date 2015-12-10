#pragma once

#include "sani/engine/messaging/channels/peer_to_peer_channel.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/forward_declare.hpp"

namespace sani {

	namespace engine {

		namespace channels {

			/// @class DocumentChannel document_channel.hpp "sani/engine/messaging/channels/document_channel.hpp"
			/// @author voidbab
			///
			/// Channel used to route document messages.
			class DocumentChannel final : public PeerToPeerChannel<messages::DocumentMessage> {
			public:
				DocumentChannel(ServiceRegistry* const serviceRegistry);
			};
		}
	}
}