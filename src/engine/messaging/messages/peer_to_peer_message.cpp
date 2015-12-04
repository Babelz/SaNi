#include "sani/engine/messaging/messages/peer_to_peer_message.hpp"

namespace sani {

	namespace engine {
		
		namespace messages {

			PeerToPeerMessage::PeerToPeerMessage(const String& contents) : Message(MessageType::PeerToPeer),
																		   contents(contents) {
			}
			PeerToPeerMessage::PeerToPeerMessage() : PeerToPeerMessage(String()) {
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