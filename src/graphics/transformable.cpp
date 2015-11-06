#include "sani/graphics/transformable.hpp"

namespace sani {

	namespace graphics {
		Transformable::Transformable() : scale(1.0f, 1.0f, 1.0f),
										 changed(false),
										 rotation(0.0f) {
		}

		Transformable::~Transformable() {
		}
	}
}