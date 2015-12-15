#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"

namespace sani {

	namespace engine {

		namespace services {

			namespace renderablemanager {

				// Used to translate element type to recipent.
				static const String recipients[] = {
					"rectangle manager",		// Rectangle.
					"triangle manager",			// Triangle.
					"sprite manager",			// Sprite.
					"circle manager"			// Circle.
				};

				static void decorateMessage(messages::DocumentMessage* const message, const RenderableManagerCommands renderableManagerCommand, const ElementType type) {
					static uint32 recipentIndex = static_cast<uint32>(type);
					static uint32 command = static_cast<uint32>(renderableManagerCommand);

					const String& recipient = recipients[recipentIndex];

					message->getRecipients().clear();

					message->getRecipients().addRecipient(recipient);
					message->setCommand(command);
				}

				void createElement(messages::DocumentMessage* const message, const ElementType type) {
					decorateMessage(message, RenderableManagerCommands::CreateElement, type);
				}

				void deleteElement(messages::DocumentMessage* const message, const ElementType type) {
					decorateMessage(message, RenderableManagerCommands::DeleteElement, type);
				}

				void queueForUpdates(messages::DocumentMessage* const message, const ElementType type) {
					decorateMessage(message, RenderableManagerCommands::EnqueueForUpdates, type);
				}

				void getElements(messages::DocumentMessage* const message, const ElementType type) {
					decorateMessage(message, RenderableManagerCommands::GetElements, type);
				}
			}
		}
	}
}