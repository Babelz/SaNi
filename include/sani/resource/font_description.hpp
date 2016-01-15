#pragma once

#include "resource_item.hpp"
#include "sani/types.hpp"
#include <vector>
#include <tuple>

namespace sani {
	
	namespace resource {

		enum class OutlineType {
			None = 0,
			Inner,
			Outer
		};

		using CharacterRegion			= std::tuple<unsigned short, unsigned short>;
		using CharacterRegionCollection = std::vector<CharacterRegion>;

		class FontDescription : public ResourceItem {
		private:
			String fontName;
			String fontPath;
			float size;
			float spacing;
			std::vector<unsigned short> characters;
			OutlineType outline;
			float32 outlineWidth;
			bool useKerning;
		public:
			// only internal
			FontDescription() : 
				size(0), spacing(0), useKerning(false), outline(OutlineType::None), outlineWidth(0.f) { }

			FontDescription(const String& name, float size, float spacing)
				: spacing(spacing), useKerning(false), outline(OutlineType::None), outlineWidth(0.f) {
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

			inline void setFontPath(const String& path) {
				fontPath = path;
			}
			inline const String& getFontPath() const {
				return fontPath;
			}

			inline void setOutlineWidth(const float32 newWidth) {
				outlineWidth = newWidth;
			}
			inline float32 getOutlineWidth() const {
				return outlineWidth;
			}

			inline void setOutlineType(const OutlineType newType) {
				outline = newType;
			}
			inline OutlineType getOutlineType() const {
				return outline;
			}

			inline void setSetCharacterRegions(CharacterRegionCollection& regions) {
				for (size_t i = 0; i < regions.size(); ++i) {
					CharacterRegion& region = regions[i];
					unsigned short start = std::get<0>(region);
					unsigned short end = std::get<1>(region);
					if (start >= end) throw std::logic_error("Start needs to be less than end!");
					characters.reserve(end - start);
					for (; start <= end; ++start) {
						characters.push_back(static_cast<unsigned short>(start));
					}
				}
			}

			inline const std::vector<unsigned short>& getCharacters() const {
				return characters;
			}
			
		};
	}
}