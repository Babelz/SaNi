#pragma once

namespace sani {

	namespace engine {

		/// @class ChannelManager channel_manager.hpp "sani/engine/messaging/channel_manager.hpp"
		/// @author voidbab
		///
		/// Class responsible of managing the channels the 
		/// services and consumers use to send messages.
		class ChannelManager {
		private:
		public:
			ChannelManager();



			~ChannelManager();
		};
	}
}