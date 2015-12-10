#include "sani/engine/messaging/channels/peer_to_peer_channel.hpp"
#include "sani/engine/services/engine_service.hpp"
#include "sani/engine/service_registry.hpp"

namespace sani {

	namespace engine {

		namespace channels {

			template <typename T>
			PeerToPeerChannel<T>::PeerToPeerChannel(ServiceRegistry* const serviceRegistry, const MessageType type) : Channel(type, serviceRegistry),
																													  messagePool(MESSAGE_POOL_PAGE_SIZE, MESSAGE_POOL_PAGES_COUNT) {
			}

			template <typename T>
			void PeerToPeerChannel<T>::flush() {
				while (!empty()) {
					T* const message = static_cast<T*>(nextMessage());

					// p2p messages should always have only one recipent.
					const String& recipentName = *message->getRecipents().begin();

					// Send the message to the recipent.
					services::EngineService* const recipent = getServiceRegistry()->locate(recipentName);
					recipent->receive(message);

					// Release handled messages.
					if (message->wasHandled()) {
						releaseMessage(message);
					}
				}
			}

			template <typename T>
			messages::Message* const PeerToPeerChannel<T>::createEmptyMessage() {
				return messagePool.allocate();
			}
			template <typename T>
			void PeerToPeerChannel<T>::releaseMessage(messages::Message* const message) {
				messagePool.deallocate(static_cast<T*>(message));
			}
		}
	}
}