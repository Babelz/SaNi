#include "sani/engine/messaging/messages/message.hpp"
#include "sani/engine/messaging/channels/channel.hpp"
#include "sani/engine/service_registry.hpp"
#include "sani/debug.hpp"

namespace sani {

	namespace engine {

		namespace channels {

			Channel::Channel(const MessageType channelType, ServiceRegistry* const serviceRegistry) : channelType(channelType),
				serviceRegistry(serviceRegistry) {
			}

			ServiceRegistry* const Channel::getServiceRegistry() {
				return serviceRegistry;
			}

			void Channel::queueMessage(messages::Message* const message) {
				messageQueue.push(message);
			}

			messages::Message* const Channel::nextMessage() {
				SANI_ASSERT(!empty());

				messages::Message* const next = messageQueue.front();
				messageQueue.pop();

				return next;
			}

			MessageType Channel::getType() const {
				return channelType;
			}

			bool Channel::empty() const {
				return messageQueue.empty();
			}

			void Channel::route(messages::Message* const message) {
				if (message->getType() != channelType) throw std::runtime_error("invalid message type for the given channel");

				queueMessage(message);
			}

			Channel::~Channel() {
			}
		}
	}
}