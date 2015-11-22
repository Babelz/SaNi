#pragma once

namespace sani {

	namespace graphics {

		/// Defines how sprites texture
		/// will be used while texturing.
		enum class SpriteTexturingMode {
			/// Texture will be fitted to the sprite.
			Fit,
			/// Texture will be used to fill the sprite.
			Fill,
			// Texturing will be defined by the user via the texture source.
			Source
		};
	}
}