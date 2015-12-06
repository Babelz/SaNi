#include "sani/engine/services/contracts/render_service_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/messaging/messages/command_message.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/engine/services/render_service.hpp"
#include "sani/engine/sani_engine.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			using namespace renderservice;

			RenderService::RenderService(engine::SaNiEngine* const engine, graphics::GraphicsDevice* const graphicsDevice) : EngineService("render service", engine),
																															 graphicsDevice(graphicsDevice),
																															 renderer(graphicsDevice) {
			}

			void RenderService::handleDocumentMessage(messages::DocumentMessage* const message) {
				const RenderServiceCommands command = static_cast<RenderServiceCommands>(message->getCommand());

				switch (command) {
				case RenderServiceCommands::GetLayers:
					break;
				default:
					break;
				}
			}
			void RenderService::handleCommandMessage(messages::CommandMessage* const message) {
				const RenderServiceCommands command = static_cast<RenderServiceCommands>(message->getCommand());

				switch (command) {
				case RenderServiceCommands::CreateLayer:
					break;
				case RenderServiceCommands::DeleteLayer:
					break;
				default:
					break;
				}
			}

			void RenderService::receive(messages::Message* const message) {
				const MessageType messageType = message->getType();

				switch (messageType) {
				case MessageType::Command:
					handleCommandMessage(static_cast<messages::CommandMessage*>(message));
					break;
				case MessageType::Document:
					handleDocumentMessage(static_cast<messages::DocumentMessage*>(message));
					break;
				default:
					break;
				}
			}
			void RenderService::update(const EngineTime& time) {
			}
		}
	}
}