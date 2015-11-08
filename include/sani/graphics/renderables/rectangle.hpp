#pragma once

#include "sani/graphics/vertex_position_color_texture.hpp"
#include "sani/graphics/renderables/renderable.hpp"

namespace sani {
	
	namespace graphics {

		/*
			TODO: impl texturing.
		*/

		/// @class Rectangle rectangle.hpp "sani/graphics/rectangle.hpp"
		/// @author voidbab
		/// 
		/// Represents a rectangle that can have a fill color, 
		/// texture and border of given color and thickness.
		/// Uses indexing for rendering.
		class Rectangle : public Renderable {
		private:
		private:
			void initialize(const float32 x, const float32 y, const float32 w, const float32 h);
		public:
			sani::math::Rectf localBounds;
			sani::math::Rectf globalBounds;

			VertexPositionColorTexture topLeftVertex;
			VertexPositionColorTexture topRightVertex;
			VertexPositionColorTexture bottomLeftVertex;
			VertexPositionColorTexture bottomRightVertex;

			VertexPositionColor topLeftBorderVertex;
			VertexPositionColor topRightBorderVertex;
			VertexPositionColor bottomLeftBorderVertex;
			VertexPositionColor bottomRightBorderVertex;

			float32 borderThickness;
			Color borderFill;

			Color fill;

			Rectangle(const float32 x, const float32 y, const float32 w, const float32 h);
			Rectangle(const sani::math::Vec2f& position, const sani::math::Vec2f& size);
		};

		inline void recomputeGeometryData(Rectangle& triangle);
		inline void recomputeVertices(Rectangle& rectangle);
		inline void recomputeBounds(Rectangle& rectangle);

		inline bool canRender(const Rectangle& rectangle, const Renderer& renderer);
		inline void render(Rectangle& rectangle, Renderer& renderer);

		inline const uint32 getVertexElementsCount(const Rectangle& rectangle);
	}
}

#include "sani/graphics/inl/rectangle.inl"