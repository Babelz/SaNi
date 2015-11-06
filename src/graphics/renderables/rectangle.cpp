#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		/*
				tl------tr
				|  \    |
				|   \   |
				|    \  |
				bl------br
		*/

		// Static const indices, just need to give these to the 
		// renderer and i will figure out the right indices.
		//const uint32 Rectangle::indices[6] = 
		//{
		//	0, 1, 2,
		//	1, 3, 2
		//};

		//Rectangle::Rectangle(const float32 x, const float32 y, const float32 w, const float32 h) {
		//	initialize(x, y, w, h);
		//}
		//Rectangle::Rectangle(const sani::math::Vec2f& position, const sani::math::Vec2f& size) {
		//	initialize(position.x, position.y, size.x, size.y);
		//}

		//void Rectangle::initialize(const float32 x, const float32 y, const float32 w, const float32 h) {
		//	topLeftVertex.vertexPositionColor.position.x = x;
		//	topLeftVertex.vertexPositionColor.position.y = y;
		//	topLeftVertex.textureCoordinates.x = 0.0f;
		//	topLeftVertex.textureCoordinates.y = 0.0f;

		//	topRightVertex.vertexPositionColor.position.x = x + w;
		//	topRightVertex.vertexPositionColor.position.y = y;
		//	topRightVertex.textureCoordinates.x = 1.0f;
		//	topRightVertex.textureCoordinates.y = 0.0f;

		//	bottomLeftVertex.vertexPositionColor.position.x = x;
		//	bottomLeftVertex.vertexPositionColor.position.y = y + h;
		//	bottomLeftVertex.textureCoordinates.x = 0.0f;
		//	bottomLeftVertex.textureCoordinates.y = 1.0f;

		//	bottomRightVertex.vertexPositionColor.position.x = x + w;
		//	bottomRightVertex.vertexPositionColor.position.y = x + y;
		//	bottomRightVertex.textureCoordinates.x = 1.0f;
		//	bottomRightVertex.textureCoordinates.y = 1.0f;

		//	setPosition(x, y);
		//	setSize(w, h);

		//	clearChanges();
		//}
		//void Rectangle::recomputeBounds() {
		//	// Compute local bounds.

		//	// Compute global bounds.
		//}

		//const math::Rectf& Rectangle::getLocalBounds() const {
		//	return math::Rectf();
		//}
		//const math::Rectf& Rectangle::getGlobalBounds() const {
		//	math::Rectf();
		//}

		//void Rectangle::render(Renderer* const renderer) {
		//}

		//void Rectangle::recomputeVertices() {
		//}

		//bool Rectangle::canRender(const Renderer* const renderer) const {
		//	// TODO: do texturing checking.
		//	const uint32 vertexElementsCount = 7;

		//	// TODO: do texturing checking.
		//	return renderer->getVertexMode() == VertexMode::Indexed && renderer->getVertexElementsCount() == vertexElementsCount &&
		//		    renderer->getRenderState() == RenderState::Polygons;
		//}

		//void Rectangle::setSize(const float32 width, const float32 height) {
		//	localBounds.w = width;
		//	localBounds.h = height;
		//}
		//void Rectangle::setSize(const math::Vec2f& size) {
		//	localBounds.w = size.x;
		//	localBounds.h = size.y;
		//}
		//void Rectangle::setWidth(const float32 width) {
		//	localBounds.w = width;
		//}
		//void Rectangle::setHeight(const float32 height) {
		//	localBounds.h = height;
		//}

		//const sani::math::Vec2f& Rectangle::getSize() const {
		//	return localBounds.size();
		//}
		//float32 Rectangle::getWidth() const {
		//	return localBounds.w;
		//}
		//float32 Rectangle::getHeight() const {
		//	return localBounds.h;
		//}
	}
}