#pragma once

#include "sani/platform/graphics/color.hpp"
#include "sani/core/math/vector3.hpp"

using namespace sani::math;

namespace sani {

	namespace graphics {

		struct VertexPositionColor {
			Vec3f position;
			Color color;

			VertexPositionColor() {
			}

			~VertexPositionColor() {
			}
		};

		typedef VertexPositionColor VPC;
	}
}