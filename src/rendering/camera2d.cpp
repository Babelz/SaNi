#include "sani/core/math/func/transform_2d.hpp"
#include "sani/rendering/camera2d.hpp"

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

		const math::Mat3f& Camera2D::transformation() const {
			return transform;
		}
		void Camera2D::computeTransformation() {
			transform = math::translate<float>(transform, -position) *
						math::scale<float>(transform, zoom) *
						math::rotate<float>(transform, rotation) *
						math::translate<float>(transform, origin);
		}

		Camera2D::~Camera2D() {
		}
	}
}