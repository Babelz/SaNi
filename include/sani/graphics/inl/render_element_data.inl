#include "sani/graphics/render_element_data.hpp"

namespace sani {

	namespace graphics {

		void updateGroupIdentifier(RenderElementData& renderElementData) {
			// TODO: is this unique for every different type of element?
			renderElementData.groupIdentifier = renderElementData.vertexElements					* offsetof(RenderElementData, vertexElements) +
								                renderElementData.indices							* offsetof(RenderElementData, indices) +
												renderElementData.offset							* offsetof(RenderElementData, offset) +
												renderElementData.texture							* offsetof(RenderElementData, texture) +
												renderElementData.effect							* offsetof(RenderElementData, effect) +
												static_cast<uint32>(renderElementData.renderMode)	* offsetof(RenderElementData, renderMode);
		}
	}
}