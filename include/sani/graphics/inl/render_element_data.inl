#include "sani/graphics/render_element_data.hpp"

namespace sani {

	namespace graphics {

		void updateGroupIdentifier(RenderElementData& renderElementData) {
			const std::hash<uint32> uint32Hash;

			renderElementData.groupIdentifier = uint32Hash(renderElementData.vertexElements + offsetof(RenderElementData, vertexElements)) +
								                uint32Hash(renderElementData.indices + offsetof(RenderElementData, indices)) +
												uint32Hash(renderElementData.offset + offsetof(RenderElementData, offset)) +
												uint32Hash(static_cast<uint32>(renderElementData.renderMode) + offsetof(RenderElementData, renderMode));
		}
	}
}