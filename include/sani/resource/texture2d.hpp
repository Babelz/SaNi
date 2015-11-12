#pragma once
#include "sani/platform/graphics/texture.hpp"
#include "sani/types.hpp"
#include "sani/resource/resource.hpp"
#include "sani/resource/serialization.hpp"
#include <vector>
#include "sani/core/math/rectangle.hpp"
SANI_FORWARD_DECLARE_3(sani, resource, reader, Texture2DReader);
SANI_FORWARD_DECLARE_2(sani, resource, Texture2DContent);
SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);

namespace sani {
	namespace resource {

		class Texture2D : public Resource, public graphics::Texture {
		private:
			typedef std::vector<unsigned char> PixelData;
			const uint32 levelCount;
			void generateTexture(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap, graphics::SurfaceFormat format, graphics::SurfaceType type);
		public:
			Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height);
			Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap, graphics::SurfaceFormat format);
			Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap, const graphics::SurfaceFormat format, const graphics::SurfaceType type);
			~Texture2D();
			static uint32 calculateLevelCount(uint32 width, uint32 height);

			void setData(graphics::GraphicsDevice* device, const int level, const math::Recti* rect, const PixelData& data, const uint32 startIndex, const uint32 elementCount);
		};
		
	}
}
// TODO this can be moved to somewhere else?
SANI_DESERIALIZABLE_WITH(sani::resource::Texture2DContent, sani::resource::reader::Texture2DReader);
//SANI_SERIALIZABLE_WITH(sani::resource::Texture2DContent, sani::resource::compiler::Texture2DWriter);

