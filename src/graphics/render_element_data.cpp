#include "sani/graphics/render_element_data.hpp"

namespace sani {

	namespace graphics {

		RenderElementData::RenderElementData() : vertexElements(0),
												 indices(0),
												 first(0),
												 last(0),
												 offset(0) {
		}

		RenderElementData::~RenderElementData() {
		}
	}
}