#include "sani/graphics/renderables/renderable.hpp"

namespace sani {

	namespace graphics {

		bool canRender(const Renderable* const renderable, const Renderer* const renderer) {
			return true;

			// TODO: polymorphic call.
		}

		void render(const Renderable* const renderable, Renderer* const renderer) {
			// TODO: polymorphic call.
		}

		void recomputeVertices(Renderable* const renderable) {
			// TODO: polymorphic call.
		}
	}
}