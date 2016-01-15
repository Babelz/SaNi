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

		/// Represents a texture graphics resource
		///
		/// 
		class Texture2D : public Resource, public graphics::Texture {
		private:
			using PixelData = std::vector<unsigned char>;
			
			const uint32 levelCount;

			/// Generates texture and sets filters 
			///
			/// @param[in] device The graphics device
			/// @param[in] width The width of the texture
			/// @param[in] height The height of the texture
			/// @param[in] mipmap Should it generate mipmaps?
			/// @param[in] format The surface format for texture
			/// @param[in] type The type of this texture
			void generateTexture(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap, graphics::SurfaceFormat format, graphics::SurfaceType type);
		public:
			/// Generates new 2D texture without mipmaps
			/// 
			/// @param[in] device The graphics device to be used to create texture
			/// @param[in] width The width of the texture
			/// @param[in] height The height of the texture
			Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height);

			/// Generates new 2D texture with specific surface format and optional mipmaps
			/// 
			/// @param[in] device The graphics device to be used to create texture
			/// @param[in] width The width of the texture
			/// @param[in] height The height of the texture
			/// @param[in] mipmap Should it generate mipmaps?
			/// @param[in] format The surface format for texture
			Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap, graphics::SurfaceFormat format);

			/// Generates new 2D texture with specific surface format and optional mipmaps
			/// 
			/// @param[in] device The graphics device to be used to create texture
			/// @param[in] width The width of the texture
			/// @param[in] height The height of the texture
			/// @param[in] mipmap Should it generate mipmaps?
			/// @param[in] format The surface format for texture
			/// @param[in] type The type of this texture
			Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap, const graphics::SurfaceFormat format, const graphics::SurfaceType type);

			/// Default deconstructor
			~Texture2D();

			/// Calculates the mip map level count
			/// 
			/// @param width The width of texture
			/// @param height The height of texture
			static uint32 calculateLevelCount(uint32 width, uint32 height);

			/// Sets the pixel data to textures level
			/// 
			/// @param[in] device The graphics device
			/// @param[in] level The mipmap level
			/// @param[in] rect The source rectangle
			/// @param[in] data The pixels to be set
			/// @param[in] startIndex The index where to start copying pixels
			/// @param[in] elementCount How many pixels to be copied
			void setData(graphics::GraphicsDevice* device, const int level, const math::Rect32i* rect, const PixelData& data, const uint32 startIndex, const uint32 elementCount);

			/// Gets the pixel data from textures level
			/// 
			/// @param[in] device The graphics device
			/// @param[in] level The mipmap level
			/// @param[in] rect The source rectangle
			/// @param[out] data The container where to read the pixel data
			/// @param[in] startIndex The index where to start copying pixels
			/// @param[in] elementCount How many pixels to be copied
			void getData(graphics::GraphicsDevice* device, const int level, const math::Rect32i* rect, PixelData& data, const uint32 startIndex, const uint32 elementCount);
		};
		
	}
}
// TODO this can be moved to somewhere else?
SANI_DESERIALIZABLE_WITH(sani::resource::Texture2DContent, sani::resource::reader::Texture2DReader);
//SANI_SERIALIZABLE_WITH(sani::resource::Texture2DContent, sani::resource::compiler::Texture2DWriter);

