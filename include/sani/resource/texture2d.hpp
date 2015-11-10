#pragma once
#include "sani/platform/graphics/texture.hpp"
#include "sani/types.hpp"
#include "sani/resource/resource.hpp"
#include "sani/resource/serialization.hpp"
#include "GL\glew.h"
SANI_FORWARD_DECLARE_3(sani, resource, reader, Texture2DReader);
SANI_FORWARD_DECLARE_2(sani, resource, Texture2DContent);
SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);

namespace sani {
	namespace resource {

		enum SurfaceFormat {
			ColorRGBA
		};

		enum SurfaceType {
			Texture,
			RenderTarget
		};

		class Texture2D : public Resource, public graphics::Texture {
		private:
			const uint32 levelCount;
			void generateTexture(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap, SurfaceFormat format, SurfaceType type);
		public:
			// TODO debug, hax dont use
			Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height);
			Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap, SurfaceFormat format);
			Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap, const SurfaceFormat format, const SurfaceType type);
			~Texture2D();
			static uint32 calculateLevelCount(uint32 width, uint32 height);
		};
		
	}
}
// TODO this can be moved to somewhere else?
SANI_DESERIALIZABLE_WITH(sani::resource::Texture2DContent, sani::resource::reader::Texture2DReader);
//SANI_SERIALIZABLE_WITH(sani::resource::Texture2DContent, sani::resource::compiler::Texture2DWriter);

