#include "sani/graphics/render_data.hpp"

namespace sani {

	namespace graphics {

		RenderData::RenderData(const uint32 vertices, const uint32 indices, const uint32 renderElements) : renderElementsCount(0)	{
			this->vertices.resize(vertices);
			
			if (indices > 0) this->vertexIndices.resize(indices);
			
			this->renderElements.resize(renderElements);
			
			renderElementIndices.resize(renderElements);
		}
		RenderData::RenderData(const uint32 vertices, const uint32 renderElements) : RenderData(vertices, 0, renderElements) {
		}

		RenderData::~RenderData() {
		}
	}
}