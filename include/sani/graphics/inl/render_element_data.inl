#include "sani/graphics/render_element_data.hpp"

namespace sani {

	namespace graphics {

		void updateHash(RenderElementData& renderElementData) {
			const std::hash<uint32> uint32Hash;

			renderElementData.hash = uint32Hash(renderElementData.vertexElements + offsetof(RenderElementData, vertexElements)) +
								     uint32Hash(renderElementData.indices + offsetof(RenderElementData, indices)) +
									 uint32Hash(renderElementData.first + offsetof(RenderElementData, first)) +
									 uint32Hash(renderElementData.last + offsetof(RenderElementData, last)) +
									 uint32Hash(renderElementData.offset + offsetof(RenderElementData, offset));
		}
	}
}