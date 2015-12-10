#include "sani/graphics/camera2d.hpp"

namespace sani {

	namespace graphics {

		Camera2D::Camera2D(Viewport& viewport) : viewport(viewport),
												 rotation(0.0f),
												 zoom(1.0f, 1.0f, 1.0f),
												 name("Camera2D") {
		}

		Camera2D::~Camera2D() {
		}

		bool Camera2D::operator ==(const Camera2D& lhs) const {
			return lhs.getName() == name;
		}
		bool Camera2D::operator !=(const Camera2D& lhs) const {
			return !(lhs.getName() == name);
		}
	}
}