#pragma once

#include "sani/engine/services/engine_service.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/graphics/camera2d.hpp"
#include "sani/graphics/layer.hpp"
#include "sani/graphics/color.hpp"

#include <vector>
#include <list>

SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);
SANI_FORWARD_DECLARE_3(sani, engine, messages, CommandMessage);

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);
SANI_FORWARD_DECLARE_2(sani, engine, SaNiEngine);
SANI_FORWARD_DECLARE_2(sani, graphics, Window);

namespace sani {

	namespace engine {
	
		namespace services {

			class RenderService final : public EngineService {
			private:
				graphics::GraphicsDevice* const graphicsDevice;
				graphics::Window* const window;

				graphics::Renderer renderer;

				std::list<graphics::Camera2D> cameras;
				std::list<graphics::Layer> layers;

				graphics::Color clearColor;

				/*
					Event handlers.
				*/

				static void windowClosed(SaNiEngine* const engine);
				static void windowSizeChanged(graphics::GraphicsDevice* const device, graphics::Window* const window, graphics::Camera2D* const camera);

				/*
					Message handling.
				*/

				void handleDocumentMessage(messages::DocumentMessage* const message);
				void handleCommandMessage(messages::CommandMessage* const message);
				
				bool initialize();

				/*
					Command functions.				
				*/

				void createLayer(messages::CommandMessage* const message);
				void deleteLayer(messages::CommandMessage* const message);
				void getLayers(messages::DocumentMessage* const message);

				void createCamera(messages::CommandMessage* const message);
				void deleteCamera(messages::CommandMessage* const message);
				void getCameras(messages::DocumentMessage* const message);

				void getClearColor(messages::DocumentMessage* const message);
				void setClearColor(messages::CommandMessage* const message);

				void getGraphicsDevice(messages::DocumentMessage* const message);
				void getWindow(messages::DocumentMessage* const message);

				void renderToCamera(const graphics::Camera2D& camera);
			protected:
				virtual bool onStart() final override;
				virtual void onTerminate() final override;
			public:
				RenderService(SaNiEngine* const engine, graphics::GraphicsDevice* const graphicsDevice, graphics::Window* const window);

				void receive(messages::Message* const message) final override;
				void update(const EngineTime& time) final override;

				~RenderService();
			};
		}
	}
}