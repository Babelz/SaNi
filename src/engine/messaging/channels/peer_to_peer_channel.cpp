#include "sani/engine/messaging/channels/peer_to_peer_channel.hpp"
#include "sani/engine/service_registry.hpp"
#include "sani/engine/services/engine_service.hpp"

namespace sani {

	namespace engine {
		
		namespace channels {

			PeerToPeerChannel::PeerToPeerChannel(ServiceRegistry* const serviceRegistry) : Channel(MessageType::PeerToPeer, serviceRegistry),
																						   messagePool(MESSAGE_POOL_PAGE_SIZE, MESSAGE_POOL_PAGES_COUNT) {
			}

			void PeerToPeerChannel::flush() {
				while (!empty()) {
					messages::PeerToPeerMessage* const message = static_cast<messages::PeerToPeerMessage*>(nextMessage());
					
					SANI_ASSERT(message->recipents.recipentsCount() == 1);

					// P2P messages should always have only one recipent.
					const String& recipentName = *message->recipents.begin();

					// Send the message to the recipent.
					services::EngineService* const recipent = getServiceRegistry()->locate(recipentName);
					recipent->receive(message);

					// Send unhandled messages to the dead letter channel.
					if (message->handled) {
						// TODO: dead letter channel.
					}
				}
			}

			messages::Message* const PeerToPeerChannel::createEmptyMessage() {
				return messagePool.allocate();
			}
			void PeerToPeerChannel::releaseMessage(messages::Message* const message) {
				messagePool.deallocate(static_cast<messages::PeerToPeerMessage*>(message));
			}
		}
	}
}