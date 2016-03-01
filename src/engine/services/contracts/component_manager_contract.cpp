#include "sani/engine/services/contracts/component_manager_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/messaging/messages/query_message.hpp"

namespace sani {

	namespace engine {

		namespace services {

			namespace componentmanager {

				void createComponent(messages::DocumentMessage* const message) {
					message->getRecipients().addRecipient("component manager");

					message->setCommand(static_cast<uint32>(ComponentManagerCommands::CreateComponent));
				}

				void destroyComponent(messages::QueryMessage* const message, const uint32 id) {
					message->getRecipients().addRecipient("component manager");

					message->setCommand(static_cast<uint32>(ComponentManagerCommands::DestroyComponent));
					message->setContents(std::to_string(id));
				}

				void listComponents(messages::DocumentMessage* const message) {
					message->getRecipients().addRecipient("component manager");

					message->setCommand(static_cast<uint32>(ComponentManagerCommands::ListComponents));
				}
			}
		}
	}
}
