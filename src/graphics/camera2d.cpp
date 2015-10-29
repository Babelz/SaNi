#include "sani/graphics/camera2d.hpp"

namespace sani {

	namespace graphics {

		Camera2D::Camera2D(Viewport& viewport) : viewport(viewport),
												 rotation(0.0f),
												 zoom(1.0f, 1.0f, 1.0f) {
		}

		Camera2D::~Camera2D() {
		}
	}
}