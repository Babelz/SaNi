#pragma once

#include "sani/resource/resource_item.hpp"
#include "sani/types.hpp"
#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/core/math/rectangle.hpp"

namespace sani {
	namespace resource {

		/// Class which represents image content
		/// used to transform from type to another type eg. PNG => TGA, RGB => BGR etc
		class BitmapContent : public ResourceItem {
		protected:
			uint32 width;
			uint32 height;
		public:
			BitmapContent(const uint32 width, const uint32 height);
			virtual ~BitmapContent();

			/// Gets the surface format for this bitmap
			/// @param[out] out nullptr if the type is not recognized or the surface format if found
			virtual void tryGetFormat(graphics::SurfaceFormat* out) const = 0;
			
			virtual void copyFrom(BitmapContent* from,
				const sani::math::Recti& sourceArea, const sani::math::Recti& destinationArea) = 0;

			inline const uint32 getWidth() const;

			inline const uint32 getHeight() const;
		};

		template <class PixelType>
		class PixelBitmapContent : public BitmapContent {
		private:
			graphics::SurfaceFormat format;
			PixelType* pixels;
			PixelBitmapContent(PixelBitmapContent const&) = delete;
			PixelBitmapContent& operator=(PixelBitmapContent const&) = delete;
		public:
			PixelBitmapContent(uint32 width, uint32 height);
			~PixelBitmapContent();
			virtual void tryGetFormat(graphics::SurfaceFormat* out) const;
			// TODO figure out something better
			void setPixel(uint32 index, const PixelType& value);

			virtual void copyFrom(BitmapContent* from,
				const sani::math::Recti& sourceArea, const sani::math::Recti& destinationArea);

			void setPixel(uint32 y, uint32 x, const PixelType& pxl);
			PixelType& getPixel(uint32 y, uint32 x) const;
		};

	}
}

#include "inl/bitmap_content.inl"