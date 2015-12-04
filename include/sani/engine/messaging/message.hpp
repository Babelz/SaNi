#pragma once	

#include "sani/engine/messaging/recipent_list.hpp"

namespace sani {

	namespace engine {

		/// @class Message message.hpp "sani/engine/messaging/message.hpp
		/// @author voidbab
		///
		/// Serves as a base class for all other messages.
		/// Represents a message that the services and consumers and use
		/// to message each other. 
		class Message {
		private:
			RecipentList recipents;

			bool handled;
		public:
			Message();

			virtual ~Message();
		};
	}
}