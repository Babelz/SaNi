#include "sani/graphics/renderables/renderable.hpp"

namespace sani {

	namespace graphics {

		Renderable::Renderable(const uint32 vertices, const uint32 indices, const uint32 renderElements, resource::Texture2D* const texture) : renderData(vertices, indices, renderElements),
																																			   texture(texture) {
		}
		Renderable::Renderable(const uint32 vertices, const uint32 indices, const uint32 renderElements) : Renderable(vertices, indices, renderElements, nullptr) {
		}
		Renderable::Renderable(const uint32 vertices, const uint32 renderElements) : Renderable(vertices, 0, renderElements, nullptr) {
		}

		Renderable::~Renderable() {
		}
	}
}