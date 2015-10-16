#pragma once	

#include "sani/graphics/vertex_position_color.hpp"

using namespace sani::math;

namespace sani {

	namespace graphics {

		struct VertexPositionColorTexture {
			VertexPositionColor vertexPositionColor;
			Vec2f textureCoordinates;

			VertexPositionColorTexture() {
			}
			
			~VertexPositionColorTexture() {
			}
		};

		typedef VertexPositionColorTexture VPCT;
	}
}