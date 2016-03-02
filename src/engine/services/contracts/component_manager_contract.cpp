#include "sani/engine/services/contracts/component_manager_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/messaging/messages/query_message.hpp"

namespace sani {

	namespace engine {

		namespace services {

			namespace componentmanager {

				void createComponent(const String& recipient, messages::DocumentMessage* const message) {
					message->getRecipients().addRecipient(recipient);

					message->setCommand(static_cast<uint32>(ComponentManagerCommands::CreateComponent));
				}

				void destroyComponent(const String& recipient, messages::QueryMessage* const message, const uint32 id) {
					message->getRecipients().addRecipient(recipient);

					message->setCommand(static_cast<uint32>(ComponentManagerCommands::DestroyComponent));
					message->setContents(std::to_string(id));
				}

				void listComponents(const String& recipient, messages::DocumentMessage* const message) {
					message->getRecipients().addRecipient(recipient);

					message->setCommand(static_cast<uint32>(ComponentManagerCommands::ListComponents));
				}
			}
		}
	}
}
