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
			const float32 znear = -1.0f;
			const float32 zfar = 1.0f;
			const float32 ar = static_cast<float32>(viewport.width) / viewport.height;

			transform = math::ortho<float32>(0.0f, static_cast<float32>(viewport.width), static_cast<float32>(viewport.height), 0.0f, znear, zfar);
			transform = math::translate(transform, position);
			transform = math::perspective<float32>(60.0f, ar, znear, zfar) * transform;
		    transform = math::rotate(transform, rotation, math::Vec3f(0.0f, 0.0f, 1.0f));
			transform = math::scale(transform, zoom);
		}

		Camera2D::~Camera2D() {
		}
	}
}