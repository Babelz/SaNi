#include "sani/core/math/func/transform.hpp"
#include "sani/graphics/camera2d.hpp"

namespace sani {
	
	namespace graphics {

		float32 Camera2D::getX() const {
			return position.x;
		}
		float32 Camera2D::getY() const {
			return position.y;
		}

		float32 Camera2D::getOriginX() const {
			return origin.x;
		}
		float32 Camera2D::getOriginY() const {
			return origin.y;
		}

		float32 Camera2D::getZoom() const {
			return zoom.x;
		}
		float32 Camera2D::getRotation() const {
			return rotation;
		}

		void Camera2D::setX(const float32 x) {
			position.x = x;
		}
		void Camera2D::setY(const float32 y) {
			position.y = y;
		}
		void Camera2D::setPosition(const math::Vec2f& position) {
			this->position.x = position.x;
			this->position.y = position.y;
		}

		void Camera2D::setOriginX(const float32 x) {
			origin.x = x;
		}
		void Camera2D::setOriginY(const float32 y) {
			origin.y = y;
		}
		void Camera2D::setOrigin(const math::Vec2f& origin) {
			this->origin.x = origin.x;
			this->origin.y = origin.y;
		}

		void Camera2D::setZoom(const float32 value) {
			zoom.x = zoom.y = zoom.z = value;
		}
		void Camera2D::setRotation(const float32 value) {
			rotation = value;
		}

		void Camera2D::moveBy(const float32 x, const float32 y) {
			position.x += x;
			position.y += y;
		}
		void Camera2D::moveBy(const math::Vec2f& amount) {
			position.x += amount.x;
			position.y += amount.y;
		}

		void Camera2D::zoomBy(const float32 amount) {
			zoom.x = zoom.y = zoom.z += amount;
		}
		void Camera2D::rotateBy(const float32 amount) {
			rotation += amount;
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
			const float32 zNear = -1.0f;
			const float32 zFar = 1.0f;
			const float32 aspectRatio = static_cast<float32>(viewport.width) / viewport.height;

			transform = math::ortho<float32>(0.0f, static_cast<float32>(viewport.width), static_cast<float32>(viewport.height), 0.0f, zNear, zFar);
			transform = math::translate(transform, -position);
			transform = math::perspective<float32>(60.0f, aspectRatio, zNear, zFar) * transform;
			transform = math::rotate(transform, rotation, math::Vec3f(0.0f, 0.0f, 1.0f));
			transform = math::scale(transform, zoom);
		}
	}
}
