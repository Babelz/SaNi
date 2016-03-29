#pragma once

#include "sani/platform/graphics/graphics_enums.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {
	
		struct TextureDescription final {
			uint32 width			{ 0 };
			uint32 height			{ 0 };
			uint32 levels			{ 0 };
			SurfaceFormat format	{ SurfaceFormat::ColorRGBA };
			TextureTarget type		{ TextureTarget::Texture2D };

			TextureDescription() = default;

			~TextureDescription() = default;
		};

		struct VertexAttributePointerDescription final {
			uint32 location		{ 0 };
			uint32 size			{ 0 };

			PrimitiveType type	{ PrimitiveType::UByte };
			bool normalized		{ false };

			uint32 stride		{ 0 };
			uint32 offset		{ 0 };

			VertexAttributePointerDescription() = default;

			~VertexAttributePointerDescription() = default;
		};

		struct BufferDescription final {
			BufferType type		{ BufferType::ArrayBuffer };
			BufferUsage usage	{ BufferUsage::Static };

			uint32 bytes		{ 0 };

			void* data	        { nullptr };

			BufferDescription() = default;
			
			~BufferDescription() = default;
		};
	}
}