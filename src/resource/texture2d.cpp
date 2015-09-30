#include "sani/resource/texture2d.hpp"

namespace sani {
	namespace resource {
		Texture2D::Texture2D(const size_t width, const size_t height)
			: width(width), height(height) {

		}

		Texture2D::~Texture2D() {}

		size_t Texture2D::getHeight() const {
			return height;
		}

		size_t Texture2D::getWidth() const {
			return width;
		}
	}
}