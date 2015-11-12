#pragma once

#include "sani/types.hpp"

namespace sani {

	class Renderable;	

	namespace graphics {

		inline void setupShapeForRendering(Renderable* const renderable, const float32 borderThickness);
	}
}

#include "sani/graphics/inl/render_helper.inl"