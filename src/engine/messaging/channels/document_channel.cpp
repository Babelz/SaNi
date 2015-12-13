#include "sani/engine/messaging/channels/document_channel.hpp"

namespace sani {

	namespace engine {
		
		namespace channels {

			DocumentChannel::DocumentChannel(ServiceRegistry* const serviceRegistry)
				: PeerToPeerChannel(serviceRegistry, MessageType::Document, messages::MessageReleaseStrategy::SenderReleases) {
			}
		}
	}
}