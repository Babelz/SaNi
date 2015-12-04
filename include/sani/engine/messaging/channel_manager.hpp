#pragma once

#include "sani/engine/messaging/channels/peer_to_peer_channel.hpp"
#include "sani/engine/messaging/channels/channel.hpp"

namespace sani {

	namespace engine {

		/// @class ChannelManager channel_manager.hpp "sani/engine/messaging/channel_manager.hpp"
		/// @author voidbab
		///
		/// Class responsible of managing the channels the 
		/// services and consumers use to send messages.
		class ChannelManager {
		private:
			channels::Channel** channels;
		public:
			ChannelManager(ServiceRegistry* const serviceRegistry);

			channels::Channel* getChannel(const MessageType type);

			/// Routes all messages once per channel.
			void route() const;

			~ChannelManager();
		};
	}
}