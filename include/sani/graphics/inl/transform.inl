#include "sani/graphics/transform.hpp"

namespace sani {

	namespace graphics {
		
		void Transform::setPosition(const sani::math::Vec3f& position) {
			this->position = position;
		}
		void Transform::setPosition(const float32 x, const float32 y) {
			position.x = x;
			position.y = y;
		}
		void Transform::setX(const float32 x) {
			position.x = x;
		}
		void Transform::setY(const float32 y) {
			position.y = y;
		}

		void Transform::setScale(const sani::math::Vec3f& scale) {
			this->scale = scale;
		}
		void Transform::setScale(const float32 horizontalScale, const float32 verticalScale) {
			scale.x = horizontalScale;
			scale.y = verticalScale;
		}
		void Transform::setHorizontalScale(const float32 scale) {
			this->scale.x = scale;
		}
		void Transform::setVerticalScale(const float32 scale) {
			this->scale.y = scale;
		}

		void Transform::setOrigin(const sani::math::Vec3f& origin) {
			this->origin = origin;
		}
		void Transform::setOrigin(const float32 x, const float32 y) {
			origin.x = x;
			origin.y = y;
		}
		void Transform::setOriginX(const float32 x) {
			origin.x = x;
		}
		void Transform::setOriginY(const float32 y) {
			origin.y = y;
		}

		void Transform::setRotation(const float32 angle) {
			rotation = angle;
		}
		void Transform::rotate(const float32 angle) {
			rotation += angle;
		}

		void Transform::move(const sani::math::Vec3f& offset) {
			position += offset;
		}
		void Transform::move(const float32 offsetX, const float32 offsetY) {
			position.x += offsetX;
			position.y += offsetY;
		}

		const sani::math::Vec3f& Transform::getPosition() const {
			return position;
		}
		float32 Transform::getX() const {
			return position.x;
		}
		float32 Transform::getY() const {
			return position.y;
		}

		const sani::math::Vec3f& Transform::getScale() const {
			return scale;
		}
		float32 Transform::getHorizontalScale() const {
			return scale.x;
		}
		float32 Transform::getVerticalScale() const {
			return scale.y;
		}

		const sani::math::Vec3f& Transform::getOrigin() const {
			return origin;
		}
		float32 Transform::getOriginX() const {
			return origin.x;
		}
		float32 Transform::getOriginY() const {
			return origin.y;
		}

		float32 Transform::getRotation() const {
			return rotation;
		}
	}
}