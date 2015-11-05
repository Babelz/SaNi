#pragma once

#include "sani/graphics/color.hpp"
#include "sani/core/math/vector3.hpp"

using namespace sani::math;

namespace sani {

	namespace graphics {

		struct VertexPositionColor {
			Vec3f position;
			Color color;

			VertexPositionColor(const Vec3f& position, const Color& color) : position(position),
																			 color(color) {
			}
			VertexPositionColor() {
			}

			~VertexPositionColor() {
			}
		};

		typedef VertexPositionColor VPC;
	}
}