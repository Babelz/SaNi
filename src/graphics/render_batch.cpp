#include "sani/graphics/render_batch.hpp"

namespace sani {

	namespace graphics {
		
		RenderBatch::RenderBatch() : verticesBegin(0),
									 verticesCount(0),
									 indicesBegin(0),
									 indicesCount(0),
									 elementsData(nullptr),
									 renderSetup(0),
									 texture(0){
		}

		void RenderBatch::resetBatch() {
			verticesBegin = 0;
			verticesCount = 0;

			indicesBegin = 0;
			indicesCount = 0;

			texture = 0;

			elementsData = nullptr;
			renderSetup = 0;
		}

		RenderBatch::~RenderBatch() {
		}
	}
}