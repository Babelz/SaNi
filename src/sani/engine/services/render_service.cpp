#include "sani/engine/services/contracts/render_service_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/messaging/messages/command_message.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/engine/messaging/state_message.hpp"
#include "sani/engine/services/render_service.hpp"
#include "sani/core/utils/string_utils.hpp"
#include "sani/core/utils/convert.hpp"
#include "sani/engine/sani_engine.hpp"
#include "sani/graphics/layer.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			using namespace renderservice;
			using namespace graphics;

			RenderService::RenderService(engine::SaNiEngine* const engine, graphics::GraphicsDevice* const graphicsDevice) : EngineService("render service", engine),
																															 graphicsDevice(graphicsDevice),
																															 renderer(graphicsDevice) {
			}

			void RenderService::handleStateMessage(StateMessage* const message) {
				if (message->oldState == ServiceState::Uninitialized) {
					// Initialize.
					renderer.initialize();
				}
			}

			void RenderService::handleDocumentMessage(messages::DocumentMessage* const message) {
				const RenderServiceCommands command = static_cast<RenderServiceCommands>(message->getCommand());

				switch (command) {
				case RenderServiceCommands::GetLayers:
					getLayers(message);
					break;
				default:
					// TODO: dead letter.
					break;
				}
			}
			void RenderService::handleCommandMessage(messages::CommandMessage* const message) {
				const RenderServiceCommands command = static_cast<RenderServiceCommands>(message->getCommand());

				switch (command) {
				case RenderServiceCommands::CreateLayer:
					createLayer(message);
					break;
				case RenderServiceCommands::DeleteLayer:
					deleteLayer(message);
					break;
				default:
					// TODO: dead letter.
					break;
				}
			}

			void RenderService::createLayer(messages::CommandMessage* const message) {
				std::vector<String> tokens;

				utils::split(message->getData(), "||", tokens, true);

				SANI_ASSERT(tokens.size() == 3);

				const String name			= tokens[0];
				const LayerType type		= static_cast<LayerType>(utils::toUInt8(tokens[1]));
				const float32 order			= utils::toFloat32(tokens[2]);
				
				layers.push_back(Layer(name, type, order));

				message->markHandled();
			}
			void RenderService::deleteLayer(messages::CommandMessage* const message) {
				const String& name = message->getData();

				auto it = std::find_if(layers.begin(), layers.end(), [&name](const Layer& layer) {
					return layer.getName() == name;
				});

				if (it != layers.end()) {
					layers.remove(*it);

					message->markHandled();
				}
			}
			void RenderService::getLayers(messages::DocumentMessage* const message) {
				std::vector<Layer* const>* results = getEngine()->allocateShared<std::vector<Layer* const>>();
				NEW_DYNAMIC_DEFAULT(std::vector<Layer* const>, results);
				
				for (Layer& layer : layers) results->push_back(&layer);

				message->setData(results);

				message->markHandled();
			}
			void RenderService::removeCamera(messages::CommandMessage* const message) {
				const String& name = message->getData();

				auto it = std::find_if(cameras.begin(), cameras.end(), ([&name](const Camera2D& camera) {
					return camera.getName() == name;
				}));

				if (it != cameras.end()) {
					cameras.remove(*it);
					
					message->markHandled();
				}
			}
			void RenderService::addCamera(messages::CommandMessage* const message) {
				const String name = message->getData();

				cameras.push_back(Camera2D(graphicsDevice->getViewport()));
				
				if (name.size() != 0) cameras.back().setName(name);
			}

			void RenderService::renderToCamera(const graphics::Camera2D& camera) {
				// Swap viewports.
				const Viewport real = graphicsDevice->getViewport();
				const math::Mat4f& transform = camera.transformation();

				graphicsDevice->setViewport(camera.getViewport());

				renderer.beginRendering(transform);

				for (Layer& layer : layers) layer.render(&renderer);

				renderer.endRendering();
				
				graphicsDevice->setViewport(real);
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
				// No need to render if there are no cameras.
				if (cameras.size() == 0) return;

				for (Camera2D& camera : cameras) renderToCamera(camera);
			}
		}
	}
}