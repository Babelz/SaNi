#pragma once

#include "sani/types.hpp"

namespace sani {

	namespace engine {

		const uint32 MESSAGE_TYPES_COUNT = 4;

		/// Defines the type of a given message.
		enum class MessageType : uint32 {
			/// Contains data and is sent back to the sender
			/// after processing.
			Document		= 0,

			/// Basic and simples message. P2P just sends
			/// and message to the recipient and has no data 
			/// associated with it.
			PeerToPeer		= 1,

			/// Request is send and a reply is requested after the
			/// processing of the request.
			RequestReply	= 2,

			/// All services can access this message.
			Event			= 3
		};
	}
}