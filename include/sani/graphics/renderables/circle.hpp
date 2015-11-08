#pragma once

#include "sani/graphics/vertex_position_color_texture.hpp"
#include "sani/graphics/renderables/renderable.hpp"
#include <vector>

namespace sani {

	namespace graphics {
		
		#define VERTICES_ROUGH_CIRCLE	9
		#define VERTICES_SMOOTH_CIRCLE	36

		class Circle : public Renderable {
		private:
			void initialize(const float32 x, const float32 y, const float32 radius, const uint32 vertices);
		public:
			sani::math::Rectf localBounds;
			sani::math::Rectf globalBounds;

			std::vector<VertexPositionColorTexture> shapeVertices;
			std::vector<VertexPositionColorTexture> borderVertices;

			float32 borderThickness;
			Color borderFill;
			
			float32 radius;
			Color fill;

			Circle(const float32 x, const float32 y, const float32 radius, const uint32 vertices);
			Circle(const sani::math::Vec2f& position, const float32 radius, const uint32 vertices);
			Circle(const float32 radius, const uint32 vertices);
			Circle(const float32 radius);
		};

		inline void recomputeGeometryData(Circle& circle);
		inline void recomputeVertices(Circle& circle);
		inline void recomputeBounds(Circle& circle);

		inline bool canRender(const Circle& circle, const Renderer& renderer);
		inline void render(Circle& circle, Renderer& renderer);

		inline const uint32 getVertexElementsCount(const Circle& circle);
	}
}

#include "sani/graphics/inl/circle.inl"