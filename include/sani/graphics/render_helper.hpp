#pragma once

#include "sani/types.hpp"

namespace sani {

	class Renderable;	

	namespace graphics {

		/// Updates element indices of the element.
		/// Element is handled as a shape.
		inline void setupShapeForRendering(Renderable* const renderable, const float32 borderThickness);
		
		/// Causes the element to use texturing when rendering.
		inline void useTexturing(Renderable* const renderable);

		/// Causes the given element to use solid fill when rendering.
		inline void useSolidFill(Renderable* const renderable);
	}
}

#include "sani/graphics/inl/render_helper.inl"