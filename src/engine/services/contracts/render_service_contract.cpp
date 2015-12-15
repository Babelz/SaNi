#include "sani/engine/services/contracts/render_service_contract.hpp"
#include "sani/engine/messaging/messages/command_message.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"

namespace sani {

	namespace engine {
		
		namespace services {
			
			namespace renderservice {
				
				template<class T>
				static void decorateMessage(T* const message, const RenderServiceCommands renderServiceCommand) {
					const uint32 command = static_cast<uint32>(renderServiceCommand);

					message->setCommand(command);
					
					message->getRecipients().clear();

					message->getRecipients().addRecipient("render service");
				}
				
				template<class T>
				static void decorateMessage(T* const message, const RenderServiceCommands renderServiceCommand, const String& data) {
					decorateMessage(message, renderServiceCommand);

					message->setData(data);
				}

				void createLayer(messages::CommandMessage* const message, const String& layerInformation) {
					decorateMessage<messages::CommandMessage>(message, RenderServiceCommands::CreateLayer, layerInformation);
				}

				void deleteLayer(messages::CommandMessage* const message, const String& layerInformation) {
					decorateMessage<messages::CommandMessage>(message, RenderServiceCommands::DeleteLayer, layerInformation);
				}

				void getLayers(messages::DocumentMessage* const message) {
					decorateMessage<messages::DocumentMessage>(message, RenderServiceCommands::GetLayers);
				}

				void createCamera(messages::CommandMessage* const message, const String& cameraInformation) {
					decorateMessage<messages::CommandMessage>(message, RenderServiceCommands::CreateCamera, cameraInformation);
				}

				void deleteCamera(messages::CommandMessage* const message, const String& cameraInformation) {
					decorateMessage<messages::CommandMessage>(message, RenderServiceCommands::DeleteCamera, cameraInformation);
				}

				void getCameras(messages::DocumentMessage* const message) {
					decorateMessage<messages::DocumentMessage>(message, RenderServiceCommands::GetCameras);
				}
			}
		}
	}
}