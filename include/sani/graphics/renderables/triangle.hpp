#pragma once

#include "sani/graphics/renderables/renderable.hpp"

namespace sani {

	namespace graphics {

		/*
			TODO: impl texturing.
		*/

		/// @class Triangle triangle.hpp "sani/graphics/triangle.hpp"
		/// @author voidbab
		/// 
		/// Represents a triangle that can have a fill color, 
		/// texture and border of given color and thickness.
		class Triangle : public Renderable {
		public:
			// Local position data.
			sani::math::Vec3f topPoint;
			sani::math::Vec3f leftPoint;
			sani::math::Vec3f rightPoint;
			
			float32 borderThickness;
			Color borderFill;

			Color fill;

			Triangle(const float32 tx, const float32 ty, const float32 lx, const float32 ly, const float32 rx, const float32 ry);
			Triangle(const sani::math::Vec2f& top, const sani::math::Vec2f& left, const sani::math::Vec2f& right);
			Triangle(const float32 x, const float32 y, const float32 width, const float32 height);
			Triangle(const sani::math::Vec2f& position, const sani::math::Vec2f& size);
			Triangle(const float32 width, const float32 height);
			Triangle();
		};

		inline void recomputeGeometryData(Triangle& triangle);
		inline void recomputeVertices(Triangle& triangle);
		inline void recomputeBounds(Triangle& triangle);
		
		inline void updateRenderData(Triangle& triangle);
	}
}

#include "sani/graphics/inl/triangle.inl"