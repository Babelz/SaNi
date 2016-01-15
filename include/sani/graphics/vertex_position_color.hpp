#pragma once

#include "sani/graphics/color.hpp"
#include "sani/core/math/vector3.hpp"

using namespace sani::math;

namespace sani {

	namespace graphics {

		/// @class VertexPositionColor vertex_position_color "sani/graphics/vertex_position_color.hpp"
		/// @author voidbab
		///
		/// Defines a vertex with position and color data.
		struct VertexPositionColor {
			Vec3f position;
			Color color;

			VertexPositionColor() = default;
			~VertexPositionColor() = default;
		};

		using VPC = VertexPositionColor;
	}
}