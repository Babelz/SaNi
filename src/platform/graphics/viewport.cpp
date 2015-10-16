#include "sani/platform/graphics/viewport.hpp"

namespace sani {
	namespace graphics {
		
		Viewport::Viewport(const uint32 x, const uint32 y, const uint32 width, const uint32 height) : x(x),
																									  y(y),
																									  width(width),
																									  height(height) {
		}
		Viewport::Viewport(const Viewport& viewport) : x(viewport.x),
													   y(viewport.y),
													   width(viewport.width),
													   height(viewport.height) {
		}
		Viewport::Viewport() : x(0),
							   y(0),
							   width(0),
							   height(0) {
		}

		Viewport::~Viewport() {
		}

		Viewport& Viewport::operator =(const Viewport& rhs) {
			x = rhs.x;
			y = rhs.y;
			
			width = rhs.width;
			height = rhs.height;

			return *this;
		}
	}
}