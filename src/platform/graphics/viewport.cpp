#include "sani/platform/graphics/viewport.hpp"

namespace sani {
	namespace graphics {
		
		Viewport::Viewport(const int32 x, const int32 y, const uint32 width, const uint32 height) : x(x),
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
	}
}