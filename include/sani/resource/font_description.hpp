#pragma once
#include "resource_item.hpp"
#include "sani/types.hpp"
#include <vector>
#include <tuple>
namespace sani {
	namespace resource {
		typedef std::tuple<unsigned short, unsigned short> CharacterRegion;
		typedef std::vector<CharacterRegion> CharacterRegionCollection;
		class FontDescription : public ResourceItem {
		private:
			String fontName;
			float size;
			float spacing;
			std::vector<unsigned short> characters;
			bool useKerning;
		public:
			// only internal
			FontDescription() : size(0), spacing(0), useKerning(false) { }
			FontDescription(const String& name, float size, float spacing)
				: spacing(spacing), useKerning(false) {
				// validate
				setFontName(name);
				setSize(size);
			}
			~FontDescription() {}

			inline float getSize() const { return size; }
			inline void setSize(float newSize) { 
				if (newSize <= 0.0f) throw std::logic_error("Size must be greater than zero");
				size = newSize; 
			}

			inline const String& getFontName() const { return fontName; }
			inline void setFontName(const String& newName) {
				if (newName.empty()) throw std::logic_error("FontName cant be empty");
				fontName = newName;
			}

			inline float getSpacing() const { return spacing; }
			inline void setSpacing(float newSpacing) {
				spacing = newSpacing;
			}

			inline bool getUseKerning() const { return useKerning; }
			inline void setUseKerning(bool newKerning) {
				useKerning = newKerning;
			}

			inline void setSetCharacterRegions(CharacterRegionCollection& regions) {
				for (size_t i = 0; i < regions.size(); ++i) {
					CharacterRegion& region = regions[i];
					uint32 start = std::get<0>(region);
					uint32 end = std::get<1>(region);
					if (start >= end) throw std::logic_error("Start needs to be less than end!");
					characters.reserve(end - start);
					for (; start <= end; ++start) {
						characters.push_back(static_cast<unsigned short>(start));
					}
				}
			}
			
		};
	}
}