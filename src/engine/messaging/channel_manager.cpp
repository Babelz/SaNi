#include "sani/engine/messaging/channel_manager.hpp"

#include <algorithm>

namespace sani {

	namespace engine {

		ChannelManager::ChannelManager(ServiceRegistry* const serviceRegistry) {
			// TODO: add adding and removing channels?
			// Create initial channels.
			channels = new channels::Channel*[4];

			channels[static_cast<uint32>(MessageType::Document)]		= nullptr;
			channels[static_cast<uint32>(MessageType::PeerToPeer)]		= new channels::PeerToPeerChannel(serviceRegistry);
			channels[static_cast<uint32>(MessageType::RequestReply)]	= nullptr;
			channels[static_cast<uint32>(MessageType::Event)]			= nullptr;
		}

		channels::Channel* ChannelManager::getChannel(const MessageType type) {
			const uint32 index = static_cast<uint32>(type);

			return channels[index];
		}

		/// Routes all messages once per channel.
		void ChannelManager::route() const {
			channels[static_cast<uint32>(MessageType::PeerToPeer)]->flush();
		}

		ChannelManager::~ChannelManager() {
			for (uint32 i = 0; i < MESSAGE_TYPES_COUNT; i++) delete channels[i];

			delete[] channels;
		}
	}
}