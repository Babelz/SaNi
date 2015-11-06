#pragma once

#include "sani/graphics/vertex_position_color_texture.hpp"
#include "sani/graphics/renderables/renderable.hpp"

namespace sani {

	namespace graphics {

		/// @class Triangle triangle.hpp "sani/graphics/triangle.hpp"
		/// @author voidbab
		/// 
		/// Represents a triangle that can have a fill color, 
		/// texture and border of given color and thickness.
		/// TODO: border not implemented.
		class Triangle : public Renderable {
		private:
			void initialize(const float32 tx, const float32 ty, const float32 lx, const float32 ly, const float32 rx, const float32 ry);
		public:
			sani::math::Vec3f topPoint;
			sani::math::Vec3f leftPoint;
			sani::math::Vec3f rightPoint;

			VertexPositionColorTexture topVertex;
			VertexPositionColorTexture leftVertex;
			VertexPositionColorTexture rightVertex;

			math::Rectf localBounds;
			math::Rectf globalBounds;

			Color fill;

			Triangle(const float32 tx, const float32 ty, const float32 lx, const float32 ly, const float32 rx, const float32 ry);
			Triangle(const sani::math::Vec2f& top, const sani::math::Vec2f& left, const sani::math::Vec2f& right);
			Triangle(const float32 x, const float32 y, const float32 width, const float32 height);
			Triangle(const float32 width, const float32 height);
		};

		inline bool canRender(const Triangle& triangle, const Renderer& renderer);
		inline void render(const Triangle& triangle, Renderer& renderer);

		inline void recomputeVertices(Triangle& triangle);
		inline void recomputeBounds(Triangle& triangle);
	}
}

#include "sani/graphics/inl/triangle.inl"