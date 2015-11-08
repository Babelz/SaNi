#pragma once

#include "sani/graphics/vertex_position_color_texture.hpp"
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
		private:
			void initialize(const float32 tx, const float32 ty, const float32 lx, const float32 ly, const float32 rx, const float32 ry);
		public:
			// Local position data.
			sani::math::Vec3f topPoint;
			sani::math::Vec3f leftPoint;
			sani::math::Vec3f rightPoint;

			// Global position data and vertex data.
			VertexPositionColorTexture topVertex;
			VertexPositionColorTexture leftVertex;
			VertexPositionColorTexture rightVertex;
			
			VertexPositionColor topBorderVertex;
			VertexPositionColor leftBorderVertex;
			VertexPositionColor rightBorderVertex;

			// TODO: should this affect the geometry data?
			float32 borderThickness;
			Color borderFill;

			Color fill;

			Triangle(const float32 tx, const float32 ty, const float32 lx, const float32 ly, const float32 rx, const float32 ry);
			Triangle(const sani::math::Vec2f& top, const sani::math::Vec2f& left, const sani::math::Vec2f& right);
			Triangle(const float32 x, const float32 y, const float32 width, const float32 height);
			Triangle(const sani::math::Vec2f& position, const sani::math::Vec2f& size);
			Triangle(const float32 width, const float32 height);
		};

		inline void recomputeGeometryData(Triangle& triangle);
		inline void recomputeVertices(Triangle& triangle);
		inline void recomputeBounds(Triangle& triangle);

		inline bool canRender(const Triangle& triangle, const Renderer& renderer);
		inline void render(Triangle& triangle, Renderer& renderer);

		inline const uint32 getVertexElementsCount(const Triangle& triangle);
	}
}

#include "sani/graphics/inl/triangle.inl"