#pragma once	

#include "sani/graphics/vertex_position_color.hpp"
#include "sani/graphics/color.hpp"
#include "sani/core/math/vector.hpp"

using namespace sani::math;

namespace sani {

	namespace graphics {

		/// @class VertexPositionColorTexture vertex_position_texture_color "sani/graphics/vertex_position_texture_color.hpp"
		/// @author voidbab
		///
		/// Defines a vertex with position, color and texture data.
		struct VertexPositionColorTexture {
			/*
				Just use the VPC here, should keep the 
				byte layout same.
			*/

			// Position and color components.
			VertexPositionColor vertexPositionColor;
			Vec2f textureCoordinates;

			VertexPositionColorTexture() = default;
			~VertexPositionColorTexture() = default;
		};

		using VPCT = VertexPositionColorTexture;
	}
}