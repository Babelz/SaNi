#pragma once

#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		const uint32 RENDER_STATES_COUNT = 3;

		/// Defines the state of the render batch.
		enum class RenderState : uint32 {
			// Renderer is waiting for user commands.
			Waiting				= 0,

			// Rendering predefined primitives.
			Polygons			= 1,
			
			// Rendering images.
			TexturedPolygons	= 2
		};
	}
}