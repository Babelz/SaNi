#pragma once

namespace sani {

	namespace engine {

		/// Defines the type of a given message.
		enum class MessageType {
			/// Contains data and is sent back to the sender
			/// after processing.
			Document,

			/// Basic and simples message. P2P just sends
			/// and message to the recipient and has no data 
			/// associated with it.
			PeerToPeer,

			/// Request is send and a reply is requested after the
			/// processing of the request.
			RequestReply,

			/// All services can access this message.
			Event
		};
	}
}