#include "sani/engine/messaging/channel_manager.hpp"

#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/messaging/messages/command_message.hpp"

#include "sani/engine/messaging/channels/document_channel.hpp"
#include "sani/engine/messaging/channels/command_channel.hpp"

#include "sani/engine/messaging/channels/query_channel.hpp"

#include "sani/core/logging/log.hpp"

#include <algorithm>

namespace sani {

	namespace engine {

		ChannelManager::ChannelManager(ServiceRegistry* const serviceRegistry) {
			// TODO: add adding and removing channels?
			// Create initial channels.
			channels = new channels::Channel*[6];

			channels[static_cast<uint32>(MessageType::Document)]		= new channels::DocumentChannel(serviceRegistry);
			channels[static_cast<uint32>(MessageType::PeerToPeer)]		= new channels::PeerToPeerChannel<messages::PeerToPeerMessage>(serviceRegistry, MessageType::PeerToPeer, messages::MessageReleaseStrategy::ReleaseWhenHandled);
			channels[static_cast<uint32>(MessageType::RequestReply)]	= nullptr;
			channels[static_cast<uint32>(MessageType::Event)]			= nullptr;
			channels[static_cast<uint32>(MessageType::Command)]			= new channels::CommandChannel(serviceRegistry);
			channels[static_cast<uint32>(MessageType::Query)]			= new channels::QueryChannel(serviceRegistry);
		}

		channels::Channel* ChannelManager::getChannel(const MessageType type) {
			const uint32 index = static_cast<uint32>(type);

			channels::Channel* const channel = channels[index];
			
			if (channel == nullptr) {
				FNCLOG_ERR(log::OutFlags::All, "channel not found");
				
				std::abort();
			}

			return channel;
		}

		ChannelManager::~ChannelManager() {
			// TODO: deleting query channels throws and exception.

			for (uint32 i = 0; i < MESSAGE_TYPES_COUNT; i++) delete channels[i];

			delete[] channels;
		}
	}
}