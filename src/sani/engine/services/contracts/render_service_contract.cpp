#include "sani/engine/services/contracts/render_service_contract.hpp"
#include "sani/engine/messaging/messages/command_message.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"

namespace sani {

	namespace engine {
		
		namespace services {
			
			namespace renderservice {
				
				static void decorateCommandMessage(messages::CommandMessage* const message, const RenderServiceCommands renderServiceCommand, const String& data) {
					const uint32 command = static_cast<uint32>(renderServiceCommand);

					message->setCommand(command);
					message->setData(data);
				}

				void createLayer(messages::CommandMessage* const message, const String& layerInformation) {
					decorateCommandMessage(message, RenderServiceCommands::CreateLayer, layerInformation);
				}

				void deleteLayer(messages::CommandMessage* const message, const String& layerInformation) {
					decorateCommandMessage(message, RenderServiceCommands::DeleteLayer, layerInformation);
				}

				void getLayers(messages::DocumentMessage* const message) {
					const uint32 command = static_cast<uint32>(RenderServiceCommands::GetLayers);

					message->setCommand(command);

					message->clearData();
				}

				bool isValidCommand(const uint32 command) {
					return command <= static_cast<uint32>(RenderServiceCommands::GetLayers);
				}
			}
		}
	}
}