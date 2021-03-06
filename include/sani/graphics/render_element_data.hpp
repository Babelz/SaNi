#pragma once

#include "sani/platform/graphics/graphics_enums.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsEffect);

namespace sani {
	
	namespace graphics {

		/// @class RenderElementData render_element_data "sani/graphics/render_element_data.hpp"
		/// @author voidbab
		///
		/// Defines how vertices of an element should be processed 
		/// and what texture and effect it will be using.
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
			// ID of the texture.
			uint32 texture;
			// ID of the effect this element is using.
			GraphicsEffect* effect;

			// Render mode that this element will use.
			RenderMode renderMode;

			// The so called "hash" used to check equality.
			uint32 groupIdentifier;

			RenderElementData();

			~RenderElementData();
		};

		inline void updateGroupIdentifier(RenderElementData& renderElementData);
	}
}

#include "sani/graphics/inl/render_element_data.inl"