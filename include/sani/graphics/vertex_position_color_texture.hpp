#pragma once	

#include "sani/graphics/vertex_position_color.hpp"
#include "sani/platform/graphics/color.hpp"
#include "sani/core/math/vector.hpp"

using namespace sani::math;

namespace sani {

	namespace graphics {

		struct VertexPositionColorTexture {
			/*
				Just use the VPC here, should keep the 
				byte layout same.
			*/

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