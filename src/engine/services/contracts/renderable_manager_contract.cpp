#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/messaging/messages/command_message.hpp"

namespace sani {

	namespace engine {
		
		namespace services {
			
			namespace renderablemanager {

				// Used to translate element type to recipent.
				static const String recipents[] = {
					"rectangle manager",		// Rectangle.
					"triangle manager",			// Triangle.
					"sprite manager",			// Sprite.
					"circle manager"			// Circle.
				};

				template <class T>
				static void decorateMessage(T* const message, const RenderableManagerCommands renderableManagerCommands, const ElementType type) {
					static uint32 command = static_cast<uint32>(renderableManagerCommands);
					static uint32 recipentIndex = static_cast<uint32>(type);

					String recipent = recipents[recipentIndex];

					message->getRecipents().clear();

					message->getRecipents().addRecipent(recipent);
					message->setCommand(command);
				}

				void createElement(messages::DocumentMessage* const message, const ElementType type) {
					decorateMessage<messages::DocumentMessage>(message, RenderableManagerCommands::CreateElement, type);
				}

				void deleteElement(messages::CommandMessage* const message, const ElementType type) {
					decorateMessage<messages::CommandMessage>(message, RenderableManagerCommands::DeleteElement, type);
				}

				void queueForUpdates(messages::CommandMessage* const message, const ElementType type) {
					decorateMessage<messages::CommandMessage>(message, RenderableManagerCommands::QueueForUpdates, type);
				}

				void getElements(messages::DocumentMessage* const message, const ElementType type) {
					decorateMessage<messages::DocumentMessage>(message, RenderableManagerCommands::GetElements, type);
				}
			}
		}
	}
}