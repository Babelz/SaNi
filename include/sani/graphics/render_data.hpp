#pragma once		

#include "sani/graphics/vertex_position_color_texture.hpp"
#include "sani/graphics/render_element_data.hpp"
#include <vector>

namespace sani {

	namespace graphics {

		/*
			Element data
				- define what to draw and how

			Data
				- defines what will be used to draw
		*/

		class RenderData {
		public:
			std::vector<VertexPositionColorTexture> vertices;
			std::vector<uint32> vertexIndices;

			std::vector<RenderElementData> renderElements;
			std::vector<uint32> renderElementIndices;
			
			// How many render elements to use while rendering.
			uint32 renderElementsCount;

			RenderData(const uint32 vertices, const uint32 indices, const uint32 renderElements);
			RenderData(const uint32 vertices, const uint32 renderElements);

			~RenderData();
		};
	}
}