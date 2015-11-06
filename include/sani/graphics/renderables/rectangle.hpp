#pragma once

#include "sani/graphics/vertex_position_color_texture.hpp"
#include "sani/graphics/renderables/renderable.hpp"

namespace sani {
	
	//namespace graphics {

	//	/// @class Rectangle rectangle.hpp "sani/graphics/rectangle.hpp"
	//	/// @author voidbab
	//	/// 
	//	/// Represents a rectangle that can have a fill color, 
	//	/// texture and border of given color and thickness.
	//	/// Uses indexing for rendering.
	//	/// TODO: border not implemented.
	//	class Rectangle : public Renderable {
	//	private:
	//		static const uint32 indices[6];

	//		sani::math::Rectf localBounds;
	//		sani::math::Rectf globalBounds;

	//		VertexPositionColorTexture topLeftVertex;
	//		VertexPositionColorTexture topRightVertex;
	//		VertexPositionColorTexture bottomLeftVertex;
	//		VertexPositionColorTexture bottomRightVertex;

	//		void initialize(const float32 x, const float32 y, const float32 w, const float32 h);
	//		void recomputeBounds();
	//	public:
	//		Rectangle(const float32 x, const float32 y, const float32 w, const float32 h);
	//		Rectangle(const sani::math::Vec2f& position, const sani::math::Vec2f& size);

	//		const math::Rectf& getLocalBounds() const override;
	//		const math::Rectf& getGlobalBounds() const override;

	//		void render(Renderer* const renderer) override;

	//		void recomputeVertices() override;

	//		bool canRender(const Renderer* const renderer) const override;

	//		void setSize(const float32 width, const float32 height);
	//		void setSize(const math::Vec2f& size);
	//		void setWidth(const float32 width);
	//		void setHeight(const float32 height);

	//		const sani::math::Vec2f& getSize() const;
	//		float32 getWidth() const;
	//		float32 getHeight() const;
	//	};
	//}
}