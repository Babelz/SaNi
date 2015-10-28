#include "sani/core/math/func/transform.hpp"
#include "sani/graphics/camera2d.hpp"

namespace sani {

	namespace graphics {

		Camera2D::Camera2D(Viewport& viewport) : viewport(viewport),
												 rotation(0.0f) {
		}

		const Viewport& Camera2D::getViewport() const {
			return viewport;
		}
		void Camera2D::setViewport(const Viewport& viewport)  {
			this->viewport = viewport;
		}

		const math::Mat4f& Camera2D::transformation() const {
			return transform;
		}
		void Camera2D::computeTransformation() {
			transform = math::ortho<float32>(0.0f, viewport.width, viewport.height, 0.0f, -1.0f, 1.0f);
			transform = math::translate(transform, position);
			transform = math::rotate(transform, rotation, math::Vec3f(0.0f, 0.0f, 1.0f));
			transform = math::scale(transform, zoom);
		}

		Camera2D::~Camera2D() {
		}
	}
}