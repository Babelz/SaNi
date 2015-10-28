#pragma once
#include <vector>
#include "sani/types.hpp"
namespace sani {
	namespace resource {
		class Texture2DContent {
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
		};
	}
}