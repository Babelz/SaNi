#include "sani/graphics/vertex_helper.hpp"

namespace sani {

	namespace graphics {

		void applyRotationToTopLeftVertex(sani::math::Vec3f& globalPosition, const sani::math::Vec3f& vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			globalPosition.x = globalPosition.x + (dx + vertexPosition.x) * cos - dy * sin;
			globalPosition.y = globalPosition.y + (dx + vertexPosition.x) * sin + dy * cos;
		}
		void applyRotationToTopRightVertex(sani::math::Vec3f& globalPosition, const sani::math::Vec3f& vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			throw std::runtime_error("not implemented");
		}
		void applyRotationToBottomLeftVertex(sani::math::Vec3f& globalPosition, const sani::math::Vec3f& vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			globalPosition.x = globalPosition.x + dx * cos - (dy + vertexPosition.y) * sin;
			globalPosition.y = globalPosition.y + dx * sin + (dy + vertexPosition.y) * cos;
		}
		void applyRotationToBottomRightVertex(sani::math::Vec3f& globalPosition, const sani::math::Vec3f& vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			globalPosition.x = globalPosition.x + (dx + vertexPosition.x) * cos - (dy + vertexPosition.y) * sin;
			globalPosition.y = globalPosition.y + (dx + vertexPosition.x) * sin + (dy + vertexPosition.y) * cos;
		}
	}
}