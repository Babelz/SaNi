#pragma once	

#include "sani/platform/graphics/color.hpp"
#include "sani/core/math/vector.hpp"

using namespace sani::math;

namespace sani {

	namespace graphics {

		struct VertexPositionColorTexture {
			Vec3f position;
			Color color;
			Vec2f uv;

			VertexPositionColorTexture() {
			}
			
			~VertexPositionColorTexture() {
			}
		};

		typedef VertexPositionColorTexture VPCT;
	}
}