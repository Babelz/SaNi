#include "sani/engine/services/contracts/resource_manager_handler_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"

namespace sani {

	namespace engine {

		namespace services {

			namespace resourcemanagerhandler {

				void getDefaultResourceManager(messages::DocumentMessage* const message) {
					message->getRecipients().addRecipient("resource manager handler");

					message->setCommand(static_cast<uint32>(ResourceManagerHandlerCommands::GetDefaultResourceManager));
				}
			}
		}
	}
}