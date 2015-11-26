#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/renderables/renderables.hpp"
#include "sani/engine/services/render_service.hpp"
#include "sani/platform/time/engine_time.hpp"
#include "sani/engine/sani_engine.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace engine {

		RenderService::RenderService(SaNiEngine* const engine, graphics::GraphicsDevice* const graphicsDevice) : EngineService("render service", engine),
																												 graphicsDevice(graphicsDevice),
																												 renderer(nullptr) {
		}

		void RenderService::onInitialize() {
			renderer = new graphics::Renderer(*graphicsDevice);
			renderer->initialize();
		}

		void RenderService::onUpdate(const EngineTime& time) {
		}

		RenderService::~RenderService() {
			delete renderer;
		}
	}
}