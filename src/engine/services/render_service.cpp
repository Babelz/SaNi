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

		bool RenderService::onInitialize() {
			renderer = new graphics::Renderer(*graphicsDevice);
			return renderer->initialize();
		}

		void RenderService::onUpdate(const EngineTime& time) {
			// TODO: fix once layering, culling etc has been implemented.
			// TODO: move geometry and renderdata updates to some manager class ASAP.
			
			//for (graphics::Renderable* const element : elements) {
			//	if		(typeid(element) == typeid(graphics::Sprite))		updateElement<graphics::Sprite>(element);
			//	else if (typeid(element) == typeid(graphics::Rectangle))	updateElement<graphics::Rectangle>(element);
			//	else if (typeid(element) == typeid(graphics::Triangle))		updateElement<graphics::Triangle>(element);
			//	else if (typeid(element) == typeid(graphics::Circle))		updateElement<graphics::Circle>(element);
			//}
			
			// TODO: layering and culling.
			for (graphics::Renderable* const element : elements) renderer->renderElement(element);
		}

		void RenderService::addElement(graphics::Renderable* const renderable) {
			elements.push_back(renderable);
		}
		void RenderService::removeElement(graphics::Renderable* const renderable) {
			elements.remove(renderable);
		}

		RenderService::~RenderService() {
			delete renderer;
		}
	}
}