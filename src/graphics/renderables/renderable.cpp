#include "sani/graphics/renderables/renderable.hpp"

namespace sani {

	namespace graphics {

		Renderable::Renderable(const uint32 vertices, const uint32 indices, const uint32 renderElements) : renderData(vertices, indices, renderElements),
																										   texture(nullptr) {
		}
		Renderable::Renderable(const uint32 vertices, const uint32 renderElements) : Renderable(vertices, 0, renderElements) {
		}

		Renderable::~Renderable() {
		}
	}
}