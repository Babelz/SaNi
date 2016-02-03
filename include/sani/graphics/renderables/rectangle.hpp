#pragma once

#include "sani/graphics/renderables/renderable.hpp"

namespace sani {
	
	namespace graphics {

		/// @class Rectangle rectangle.hpp "sani/graphics/renderables/rectangle.hpp"
		/// @author voidbab
		/// 
		/// Represents a rectangle that can have a fill color, 
		/// texture and border of given color and thickness.
		/// Uses indexing for rendering.
		class Rectangle final : public Renderable {
		public:
			/*
				Element data layout
					- shape element @index 0
					- border element @index 1
					- 6 indices per element
					- 4 vertices ver element
						- 6-9 vertex elements for the shape
						- 6 elements for the border (no texturing)
			*/

			float32 borderThickness;
			Color borderFill;

			Color fill;

			Rectangle(const float32 x, const float32 y, const float32 w, const float32 h);
			Rectangle(const math::Vec2f& position, const math::Vec2f& size);
			
			Rectangle() = default;
		};

		inline void recomputeVertices(Rectangle& rectangle);
		inline void recomputeBounds(Rectangle& rectangle);

		inline void updateRenderData(Rectangle& rectangle);
	}
}

#include "sani/graphics/inl/rectangle.inl"