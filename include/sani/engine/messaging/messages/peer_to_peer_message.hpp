#pragma once

#include "sani/engine/messaging/messages/message.hpp"

namespace sani {
	
	namespace engine {
		
		namespace messages {

			/// @class PeerToPeerMessage peer_to_peer_message.hpp "sani/engine/messaging/messages/peer_to_peer_message.hpp"
			/// @author voidbab
			///
			/// Represents a simple one-way p2p message.
			class PeerToPeerMessage final : public Message {
			private:
				// Contents of the message.
				String contents;
			public:
				PeerToPeerMessage(const String& contents);
				PeerToPeerMessage();

				/// Returns the contents for this message.
				const String& getContents() const;
				/// Sets this messages contents.
				void setContents(const String& contents);
			};
		}
	}
}