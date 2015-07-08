#include "sani/platform/viewport.hpp"

namespace sani {
	namespace graphics {
		
		Viewport::Viewport(const uint32 x, const uint32 y, const uint32 width, const uint32 height) : x(x),
																									  y(y),
																									  width(width),
																									  height(height) {
		}
		Viewport::Viewport(const Viewport& viewport) : x(viewport.x),
													   y(viewport.y),
													   width(viewport.getWidth()),
													   height(viewport.getHeight()) {
		}

		// Public members.
		
		uint32 Viewport::getX() const {
			return x;
		}
		uint32 Viewport::getY() const {
			return y;
		}

		uint32 Viewport::getWidth() const {
			return width;
		}
		uint32 Viewport::getHeight() const {
			return height;
		}

		Viewport::~Viewport() {
		}

		// Operators.


		Viewport& Viewport::operator =(const Viewport& rhs) {
			x = rhs.x;
			y = rhs.y;

			width = rhs.width;
			height = rhs.height;

			return *this;
		}
	}
}