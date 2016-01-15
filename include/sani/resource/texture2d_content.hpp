#pragma once

#include <vector>
#include "sani/types.hpp"
#include "sani/resource/resource_item.hpp"

namespace sani {

	namespace resource {

		class Texture2DContent : public ResourceItem {
		private:
			using PixelData		= std::vector<unsigned char>;
			using MipmapChain	= std::vector<PixelData>;

			MipmapChain faces;
			const uint32 width;
			const uint32 height;
		public:
			Texture2DContent(const uint32 width, const uint32 height, const PixelData&);

			void generateMipmaps(bool overwrite = false);

			const MipmapChain& getMipmaps() const;

			const uint32 getWidth() const;
			const uint32 getHeight() const;
		};
	}
}