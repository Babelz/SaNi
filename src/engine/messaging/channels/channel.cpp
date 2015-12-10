#include "sani/engine/messaging/messages/message.hpp"
#include "sani/engine/messaging/channels/channel.hpp"
#include "sani/engine/service_registry.hpp"
#include "sani/debug.hpp"

namespace sani {

	namespace engine {

		namespace channels {

			Channel::Channel(const MessageType channelType, ServiceRegistry* const serviceRegistry, const messages::MessageReleaseStrategy messageReleaseStrategy) 
				: channelType(channelType),																																					 
				  serviceRegistry(serviceRegistry),
				  messageReleaseStrategy(messageReleaseStrategy) {
			}

			messages::MessageReleaseStrategy Channel::getMessageReleaseStrategy() const {
				return messageReleaseStrategy;
			}
			ServiceRegistry* const Channel::getServiceRegistry() {
				return serviceRegistry;
			}

			MessageType Channel::getType() const {
				return channelType;
			}

			void Channel::route(messages::Message* const message) {
				if (message->getType() != channelType) throw std::runtime_error("invalid message type for the given channel");

				routeMessage(message);
			}

			Channel::~Channel() {
			}
		}
	}
}