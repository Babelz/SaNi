#pragma once
#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/types.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);
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
			uint32 renderTexture;
		public:
			Texture(GraphicsDevice* device, const uint32 width, const uint32 height);
			virtual ~Texture();
			uint32 getWidth() const;
			uint32 getHeight() const;

			uint32 getID() const;
			// TODO: add support for deleting the textures.
		};
	}
}