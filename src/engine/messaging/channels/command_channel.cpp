#include "sani/engine/messaging/channels/command_channel.hpp"

namespace sani {

	namespace engine {
		
		namespace channels {

			CommandChannel::CommandChannel(ServiceRegistry* const serviceRegistry) 
				: PeerToPeerChannel(serviceRegistry, MessageType::Command, messages::MessageReleaseStrategy::ReleaseWhenHandled) {
			}
		}
	}
}