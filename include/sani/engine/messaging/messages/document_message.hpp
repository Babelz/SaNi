#pragma once

#include "sani/engine/messaging/messages/message.hpp"

namespace sani {

	namespace engine {
		
		namespace messages {

			class DocumentMessage final : public Message {
			private:
				uint32 command;

				void* data;
			public:
				DocumentMessage();

				void setCommand(const uint32 command);
				uint32 getCommand() const;

				void setData(void* const data);
				void* getData();

				void clearData();
			};
		}
	}
}