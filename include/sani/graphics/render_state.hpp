#pragma once

#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		#define STATES_COUNT 6

		enum RenderState : uint32 {
			// Renderer is waiting for user commands.
			Waiting				= 0,

			// Rendering user defined primitives.
			UserPrimitives		= 1,

			// Rendering predefined primitives.
			Primitives			= 2,
			
			// Rendering images.
			Textures			= 3,
			
			// Rendering simple text.
			Text				= 4,

			// Rendering rich text.
			RichText			= 5
		};
	}
}