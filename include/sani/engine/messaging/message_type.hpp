#pragma once

#include "sani/types.hpp"

namespace sani {

	namespace engine {

		const uint32 MESSAGE_TYPES_COUNT = 5;

		/// Enum of supported message types.
		enum class MessageType : uint32 {
			/// Contains data and is sent back to the sender
			/// after processing. Sent trough the p2p channel.
			Document		= 0,

			/// Basic and simples message. P2P just sends
			/// and message to the recipient and has no data 
			/// associated with it.
			PeerToPeer		= 1,

			/// Request is send and a reply is requested after the
			/// processing of the request. Sent trough the request p2p channel.
			RequestReply	= 2,

			/// All services can access this message.
			/// Sent trough the global channel and 
			/// removed once handled.
			Event			= 3,

			/// Message that contains a command that will be
			/// interpreted by the recipient(s). Can also contain
			/// additional command data in a form of a string and 
			/// can have a return value that the sender can
			/// and should inspect after the message has been 
			/// flagged as handled. Commands are sent trough 
			/// p2p channel.
			Command			= 4,

			/// Message that has some contents, command and 
			/// must return some result value. If the message
			/// does not return a result after processing,
			/// it should be handled as failed.
			Query			= 5
		};
	}
}