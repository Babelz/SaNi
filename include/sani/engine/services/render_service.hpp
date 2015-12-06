#pragma once

#include "sani/engine/services/engine_service.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/graphics/layer.hpp"

#include <vector>

SANI_FORWARD_DECLARE_3(sani, engine, message, DocumentMessage);
SANI_FORWARD_DECLARE_3(sani, engine, message, CommandMessage);

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);
SANI_FORWARD_DECLARE_2(sani, engine, SaNiEngine);

namespace sani {

	namespace engine {
	
		namespace services {

			class RenderService final : public EngineService {
			private:
				graphics::GraphicsDevice* const graphicsDevice;
				graphics::Renderer const renderer;

				std::vector<graphics::Layer> layers;

				void handleDocumentMessage(messages::DocumentMessage* const message);
				void handleCommandMessage(messages::CommandMessage* const message);
			
				void createLayer(messages::CommandMessage* const message);
				void deleteLayer(messages::CommandMessage* const message);
				void getLayers(messages::DocumentMessage* const message);
			public:
				RenderService(engine::SaNiEngine* const engine, graphics::GraphicsDevice* const graphicsDevice);

				void receive(messages::Message* const message) final override;
				void update(const EngineTime& time) final override;
			};
		}
	}
}