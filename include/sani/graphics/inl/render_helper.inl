#include "sani/graphics/renderables/renderable.hpp"
#include "sani/graphics/render_helper.hpp"

namespace sani {

	namespace graphics {

		void setupShapeForRendering(Renderable* const renderable, const float32 borderThickness) {
			renderable->renderData.renderElementsCount = 1;
			
			if (borderThickness > 0.0f) {
				renderable->renderData.renderElementsCount++;

				renderable->renderData.renderElementIndices[0] = 1;
				renderable->renderData.renderElementIndices[1] = 0;
			} else {
				renderable->renderData.renderElementIndices[0] = 0;
				renderable->renderData.renderElementIndices[1] = 1;
			}
		}

		void useTexturing(Renderable* const renderable) {
			assert(renderable->texture != nullptr);

			RenderElementData& shapeRenderData = renderable->renderData.renderElements[0];
			shapeRenderData.vertexElements = 9;
			shapeRenderData.texture = renderable->texture->getID();
			shapeRenderData.offset = 0;
		}

		void useSolidFill(Renderable* const renderable) {
			assert(renderable->texture == nullptr);

			RenderElementData& shapeRenderData = renderable->renderData.renderElements[0];
			shapeRenderData.vertexElements = 7;
			shapeRenderData.texture = 0;
			shapeRenderData.offset = 2;
		}
	}
}