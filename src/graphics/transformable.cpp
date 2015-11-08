#include "sani/graphics/Transform.hpp"

namespace sani {

	namespace graphics {
		Transform::Transform() : scale(1.0f, 1.0f, 1.0f),
										 rotation(0.0f) {
		}

		Transform::~Transform() {
		}
	}
}