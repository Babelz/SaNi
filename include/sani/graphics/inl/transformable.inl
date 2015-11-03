#include "sani/core/math/vector.hpp"

namespace sani {

	namespace graphics {
		
		bool Transformable::hasChanged() const {
			return changed;
		}
		void Transformable::clearChanges() {
			changed = false;
		}

		void Transformable::setPosition(const sani::math::Vec3f& position) {
			this->position = position;

			changed = true;
		}
		void Transformable::setPosition(const float32 x, const float32 y) {
			position.x = x;
			position.y = y;

			changed = true;
		}
		void Transformable::setX(const float32 x) {
			position.x = x;

			changed = true;
		}
		void Transformable::setY(const float32 y) {
			position.y = y;

			changed = true;
		}

		void Transformable::setScale(const sani::math::Vec3f& scale) {
			this->scale = scale;

			changed = true;
		}
		void Transformable::setScale(const float32 horizontalScale, const float32 verticalScale) {
			scale.x = horizontalScale;
			scale.y = verticalScale;

			changed = true;
		}
		void Transformable::setHorizontalScale(const float32 scale) {
			this->scale.x = scale;

			changed = true;
		}
		void Transformable::setVerticalScale(const float32 scale) {
			this->scale.y = scale;

			changed = true;
		}

		void Transformable::setOrigin(const sani::math::Vec3f& origin) {
			this->origin = origin;

			changed = true;
		}
		void Transformable::setOrigin(const float32 x, const float32 y) {
			origin.x = x;
			origin.y = y;

			changed = true;
		}
		void Transformable::setOriginX(const float32 x) {
			origin.x = x;

			changed = true;
		}
		void Transformable::setOriginY(const float32 y) {
			origin.y = y;

			changed = true;
		}

		void Transformable::setRotation(const float32 angle) {
			rotation = angle;

			changed = true;
		}
		void Transformable::rotate(const float32 angle) {
			rotation += angle;

			changed = true;
		}

		void Transformable::move(const sani::math::Vec3f& offset) {
			position += offset;

			changed = true;
		}
		void Transformable::move(const float32 offsetX, const float32 offsetY) {
			position.x += offsetX;
			position.y += offsetY;

			changed = true;
		}

		const sani::math::Vec3f Transformable::getPosition() const {
			return position;
		}
		float32 Transformable::getX() const {
			return position.x;
		}
		float32 Transformable::getY() const {
			return position.y;
		}

		const sani::math::Vec3f Transformable::getScale() const {
			return scale;
		}
		float32 Transformable::getHorizontalScale() const {
			return scale.x;
		}
		float32 Transformable::getVerticalScale() const {
			return scale.y;
		}

		const sani::math::Vec3f Transformable::getOrigin() const {
			return origin;
		}
		float32 Transformable::getOriginX() const {
			return origin.x;
		}
		float32 Transformable::getOriginY() const {
			return origin.y;
		}

		float32 Transformable::getRotation() const {
			return rotation;
		}
	}
}