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

		/// @class RenderData render_data "sani/graphics/render_data.hpp"
		/// @author Voidbab
		///
		/// Defines the render data of and object.
		/// Render data contains vertex, index, element and element index data.
		class RenderData {
		public:
			std::vector<VertexPositionColorTexture> vertices;		// Vertex data of the object.
			std::vector<uint32> vertexIndices;						// Vertex indices of the object.

			std::vector<RenderElementData> renderElements;			// Render elements of the object.
			std::vector<uint32> renderElementIndices;				// Render element indices of the object.
			
			// How many render elements to use while rendering.
			uint32 renderElementsCount;

			RenderData(const uint32 vertices, const uint32 indices, const uint32 renderElements);
			RenderData(const uint32 vertices, const uint32 renderElements);

			~RenderData();
		};
	}
}