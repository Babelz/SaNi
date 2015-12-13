#include "sani/engine/messaging/messages/peer_to_peer_message.hpp"

namespace sani {

	namespace engine {
		
		namespace messages {

			PeerToPeerMessage::PeerToPeerMessage() : Message(MessageType::PeerToPeer) {
			}

			const String& PeerToPeerMessage::getContents() const {
				return contents;
			}
			void PeerToPeerMessage::setContents(const String& contents) {
				this->contents = contents;
			}
		}
	}
}