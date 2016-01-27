#include "sani/graphics/graphics_effect.hpp"
#include "sani/graphics/render_element_data.hpp"

namespace sani {

	namespace graphics {

		void updateGroupIdentifier(RenderElementData& renderElementData) {
			const uint32 effect = renderElementData.effect == nullptr ? 0 : renderElementData.effect->getEffect();

			// Not sure if this is unique every time.
			// If rendering errors start popping check this.
			renderElementData.groupIdentifier = renderElementData.vertexElements					* offsetof(RenderElementData, vertexElements) +
								                renderElementData.indices							* offsetof(RenderElementData, indices) +
												renderElementData.offset							* offsetof(RenderElementData, offset) +
												renderElementData.texture							* offsetof(RenderElementData, texture) +
												effect												* offsetof(RenderElementData, effect) +
												static_cast<uint32>(renderElementData.renderMode)	* offsetof(RenderElementData, renderMode);
		}
	}
}