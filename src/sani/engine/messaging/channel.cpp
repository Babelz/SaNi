#include "sani/engine/messaging/message.hpp"
#include "sani/engine/messaging/channel.hpp"
#include "sani/engine/service_registry.hpp"
#include "sani/debug.hpp"

namespace sani {

	namespace engine {

		Channel::Channel(const MessageType channelType, ServiceRegistry* const serviceRegistry) : channelType(channelType),
																								  serviceRegistry(serviceRegistry) {
		}

		ServiceRegistry* const Channel::getServiceRegistry() {
			return serviceRegistry;
		}

		void Channel::queueMessage(Message* const message) {
			messageQueue.push(message);
		}

		Message* const Channel::nextMessage() {
			SANI_ASSERT(!empty());

			Message* const next = messageQueue.front();
			messageQueue.pop();

			return next;
		}

		bool Channel::empty() const {
			return messageQueue.empty();
		}
		
		void Channel::route(Message* const message) {
			//if (message->)
		}

		Channel::~Channel() {
		}
	}
}