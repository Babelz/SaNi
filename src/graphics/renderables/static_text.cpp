#include "sani/graphics/renderables/static_text.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/render_target_2d.hpp"
#include "sani/resource/sprite_font.hpp"

namespace sani {

	namespace graphics {

		StaticText::StaticText(GraphicsDevice* const graphicsDevice, resource::SpriteFont* const font, const float32 x, const float32 y, const float32 w, const float32 h)
			: font(font), Renderable(4, 6, 1), graphicsDevice(graphicsDevice), renderTarget(nullptr) {

			SANI_ASSERT(graphicsDevice != nullptr);
			SANI_ASSERT(font != nullptr);

			color = color::Red;

			transform.position.x = x;
			transform.position.y = y;

			transform.origin.x = w / 2.0f;
			transform.origin.y = h / 2.0f;

			localBounds.w = w;
			localBounds.h = h;

			RenderElementData& textRenderData = renderData.renderElements[0];
			textRenderData.first = 0;
			textRenderData.last = 3;
			textRenderData.vertexElements = 9;
			textRenderData.offset = 0;
			textRenderData.indices = 6;

			renderData.renderElementsCount = 1;

			renderData.vertexIndices[0] = 0;
			renderData.vertexIndices[1] = 1;
			renderData.vertexIndices[2] = 2;

			renderData.vertexIndices[3] = 1;
			renderData.vertexIndices[4] = 3;
			renderData.vertexIndices[5] = 2;
		}
		StaticText::StaticText(GraphicsDevice* const device, resource::SpriteFont* const font, const math::Vec2f& position, const math::Vec2f& size) 
			: StaticText(device, font, position.x, position.y, size.x, size.y) {
		}
		StaticText::StaticText(GraphicsDevice* const device, resource::SpriteFont* const font, const math::Rect32f& bounds) 
			: StaticText(device, font, bounds.x, bounds.y, bounds.w, bounds.h) {
		}

		StaticText::~StaticText() {
			if (renderTarget != nullptr) {
				// Assume it gets disposed...
				// TODO: add some exception checks.
				renderTarget->dispose();

				renderTarget = nullptr;
			}
		}
	}
}