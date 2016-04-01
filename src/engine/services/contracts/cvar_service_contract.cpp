#include "sani/engine/services/contracts/cvar_service_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/messaging/messages/query_message.hpp"

namespace sani {

	namespace engine {

		namespace services {

			namespace cvarservice {

				template <class T>
				static void decorateMessage(T* const message, const CVarServiceCommands cVarServiceCommand) {
					const uint32 command = static_cast<uint32>(cVarServiceCommand);

					message->getRecipients().addRecipient("cvar service");
					message->setCommand(command);
				}

				void getCVar(messages::QueryMessage* const message, const String& name) {
					decorateMessage<messages::QueryMessage>(message, CVarServiceCommands::GetCVar);
					message->setContents(name);
				}

				void listCVars(messages::DocumentMessage* const message) {
					decorateMessage<messages::DocumentMessage>(message, CVarServiceCommands::ListCVars);
				}
			}
		}
	}
}