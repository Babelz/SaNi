#include "sani/engine/messaging/channel_manager.hpp"

#include <algorithm>

namespace sani {

	namespace engine {

		ChannelManager::ChannelManager(ServiceRegistry* const serviceRegistry) {
			// TODO: add adding and removing channels?
			// Create initial channels.
			channels = new channels::Channel*[4];

			channels[0] = nullptr;
			channels[1] = new channels::PeerToPeerChannel(serviceRegistry);
			channels[2] = nullptr;
			channels[3] = nullptr;
		}

		channels::Channel* ChannelManager::getChannel(const MessageType type) {
			const uint32 index = static_cast<uint32>(type);

			return channels[index];
		}

		/// Routes all messages once per channel.
		void ChannelManager::route() const {
			for (uint32 i = 0; i < MESSAGE_TYPES_COUNT; i++) channels[i]->flush();
		}

		ChannelManager::~ChannelManager() {
			for (uint32 i = 0; i < MESSAGE_TYPES_COUNT; i++) delete channels[i];

			delete[] channels;
		}
	}
}