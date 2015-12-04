#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/engine/services/render_service.hpp"
#include "sani/engine/sani_engine.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			RenderService::RenderService(engine::SaNiEngine* const engine, graphics::GraphicsDevice* const graphicsDevice) : EngineService("render service", engine),
																															 graphicsDevice(graphicsDevice),
																															 renderer(graphicsDevice) {
			}

			void RenderService::receive(messages::Message* const message) {
			}
			void RenderService::update(const EngineTime& time) {
			}
		}
	}
}