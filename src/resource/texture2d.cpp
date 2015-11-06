#include "sani/resource/texture2d.hpp"

namespace sani {
	namespace resource {
		Texture2D::Texture2D(const uint32 width, const uint32 height)
			: width(width), height(height) {

		}

		Texture2D::~Texture2D() {}

		uint32 Texture2D::getHeight() const {
			return height;
		}

		uint32 Texture2D::getWidth() const {
			return width;
		}
	}
}