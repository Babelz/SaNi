#pragma once

namespace sani {

	namespace engine {
		
		namespace messages {

			/// Defines how channels release their messages.
			enum class MessageReleaseStrategy {
				/// Message is released when it 
				/// has been handled.
				ReleaseWhenHandled,
				
				/// Sender must release the message.
				SenderReleases
			};
		}
	}
}