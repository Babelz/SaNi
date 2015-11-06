#pragma once
#include <vector>
#include "sani/types.hpp"
#include "sani/resource/resource_item.hpp"

namespace sani {
	namespace resource {
		class Texture2DContent : public ResourceItem {
		private:
			typedef std::vector<unsigned char> PixelData;
			typedef std::vector<PixelData> MipmapChain;
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