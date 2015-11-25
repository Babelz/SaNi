#pragma once

namespace sani {

	namespace graphics {

		/// Defines how and layer should be handled by the renderer.
		enum class LayerType {
			/// Static layers are rendered once and the results 
			/// can be used many times.
			Static,
			
			/// Dynamic layers are rendered each frame.
			Dynamic
		};
	}
}