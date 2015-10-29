#pragma once

namespace sani {

	namespace graphics {

		enum RenderState {
			// Renderer is waiting for user commands.
			Waiting,

			// Rendering user defined primitives.
			UserPrimitives,

			// Rendering predefined primitives.
			Primitives,
			
			// Rendering images.
			Images,
			
			// Rendering simple text.
			Text,

			// Rendering rich text.
			RichText
		};
	}
}