#pragma once

#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/types.hpp"

namespace sani {
	
	namespace graphics {

		class RenderElementData {
		public:
			// How many elements each vertex contains.
			uint32 vertexElements;
			// How many indices this element contains.
			uint32 indices;
			// First element position.
			uint32 first;
			// Last element position.
			uint32 last;
			// Offset from the end of an vertex to the beginning of the next.
			uint32 offset;

			// Render mode that this element will use.
			RenderMode renderMode;

			RenderElementData();

			~RenderElementData();
		};
	}
}