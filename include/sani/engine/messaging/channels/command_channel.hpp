#pragma once

#include "sani/engine/messaging/channels/peer_to_peer_channel.hpp"
#include "sani/engine/messaging/messages/command_message.hpp"
#include "sani/forward_declare.hpp"

namespace sani {

	namespace engine {

		namespace channels {
			/// @class CommandChannel command_channel.hpp "sani/engine/messaging/channels/command_channel.hpp"
			/// @author voidbab
			///
			/// Channel used to route document messages.
			class CommandChannel final : public PeerToPeerChannel<messages::CommandMessage> {
			public:
				CommandChannel(ServiceRegistry* const serviceRegistry);
			};
		}
	}
}