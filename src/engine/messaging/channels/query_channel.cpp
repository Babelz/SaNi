#include "sani/engine/messaging/message_releasing_strategy.hpp"
#include "sani/engine/messaging/channels/query_channel.hpp"

namespace sani {

	namespace engine {
		
		namespace channels {

			QueryChannel::QueryChannel(ServiceRegistry* const serviceRegistry) 
				: PeerToPeerChannel(serviceRegistry, MessageType::Query, messages::MessageReleaseStrategy::SenderReleases) {
			}
		}
	}
}