#pragma once

#include "sani/graphics/vertex_position_color_texture.hpp"
#include "sani/graphics/renderables/shape.hpp"

namespace sani {

	namespace graphics {

		/// @class Triangle triangle.hpp "sani/graphics/triangle.hpp"
		/// @author voidbab
		/// 
		/// Represents a triangle that can have a fill color, 
		/// texture and border of given color and thickness.
		/// TODO: border not implemented.
		class Triangle : public Shape {
		private:
			sani::math::Vec3f topPoint;
			sani::math::Vec3f leftPoint;
			sani::math::Vec3f rightPoint;

			VertexPositionColorTexture topVertex;
			VertexPositionColorTexture leftVertex;
			VertexPositionColorTexture rightVertex;

			math::Rectf localBounds;
			math::Rectf globalBounds;

			void initialize(const float32 tx, const float32 ty, const float32 lx, const float32 ly, const float32 rx, const float32 ry);
			void recomputeBounds();
		public:
			/*
				TODO: vec2 or vec3? wtf...
			*/

			Triangle(const float32 tx, const float32 ty, const float32 lx, const float32 ly, const float32 rx, const float32 ry);
			Triangle(const sani::math::Vec2f& top, const sani::math::Vec2f& left, const sani::math::Vec2f& right);
			Triangle(const float32 x, const float32 y, const float32 width, const float32 height);
			Triangle(const float32 width, const float32 height);
			
			const math::Rectf& getLocalBounds() const override;
			const math::Rectf& getGlobalBounds() const override;
			
			void render(Renderer* const renderer) override;

			void recomputeVertices() override;

			bool canRender(const Renderer* const renderer) const override;

			/// Returns the top points local coordinates.
			sani::math::Vec2f getTop() const;
			/// Returns the left points local coordinates.
			sani::math::Vec2f getLeft() const;
			/// Returns the right points local coordinates.
			sani::math::Vec2f getRight() const;

			/// Sets the top points local coordinates.
			void setTop(const Vec2f& top);
			/// Sets the right points local coordinates.
			void setRight(const Vec2f& right);
			/// Sets the left points local coordinates.
			void setLeft(const Vec2f& left);

			/// Sets the top points coordinates.
			void setTop(const float32 x, const float32 y);
			/// Sets the right points coordinates.
			void setRight(const float32 x, const float32 y);
			/// Sets the left points coordinates.
			void setLeft(const float32 x, const float32 y);
		};
	}
}