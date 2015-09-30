#include "sani/precompiled.hpp"
#include "sani/platform/graphics/graphics_device.hpp"

namespace sani {
	namespace graphics {

		/*
			TODO: create base Texture class that holds no dimensional data?
		*/

		/// @class Texture "sani/platform/texture.hpp"
		///
		/// Represents an abstract texture that contains
		/// basic information such as size and id of the
		/// texture.
		class Texture {
		private:
			const uint32 width;
			const uint32 height;
		protected:
			// Identifier of the texture, required atleast by the OpenGL.
			RenderTexture renderTexture;
		public:
			Texture(GraphicsDevice& device, const uint32 width, const uint32 height);

			uint32 getWidth() const;
			uint32 getHeight() const;

			uint32 getID() const;

			// TODO: add support for deleting the textures.
		};
	}
}