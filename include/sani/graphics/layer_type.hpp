#pragma once

namespace sani {

	namespace graphics {

		/// Defines how and layer should be handled by the renderer.
		enum class LayerType : uint8 {
			/// Static layers are rendered once and the results 
			/// can be used many times.
			Static		= 0,
			
			/// Dynamic layers are rendered each frame.
			Dynamic		= 1
		};
	}
}