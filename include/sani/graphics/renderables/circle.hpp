#pragma once

#include "sani/graphics/renderables/renderable.hpp"
#include <vector>

namespace sani {

	namespace graphics {
		
		const uint32 VERTICES_ROUGH_CIRCLE = 9;
		const uint32 VERTICES_SMOOTH_CIRCLE = 36;

		/// @class Circle circle.hpp "sani/graphics/renderables/circle.hpp"
		/// @author voidbab
		/// 
		/// Represents a circle that can have a fill color, 
		/// texture and border of given color and thickness.
		class Circle final : public Renderable {
		public:
			float32 borderThickness;
			Color borderFill;
			
			float32 radius;
			Color fill;

			uint32 vertices;

			Circle(const float32 x, const float32 y, const float32 radius, const uint32 vertices);
			Circle(const math::Vec2f& position, const float32 radius, const uint32 vertices);
			Circle(const float32 radius, const uint32 vertices);
			Circle(const float32 radius);
			
			~Circle() = default;
		};

		inline void recomputeVertices(Circle& circle);
		inline void recomputeBounds(Circle& circle);

		inline void updateRenderData(Circle& circle);
	}
}

#include "sani/graphics/inl/circle.inl"