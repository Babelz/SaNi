#include "sani/graphics/renderables/renderable.hpp"
#include "sani/resource/texture2d.hpp"

namespace sani {

	namespace graphics {

		Renderable::Renderable() : texture(nullptr) {
		}

		Renderable::~Renderable() {
		}
	}
}