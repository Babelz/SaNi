#include "sani/platform/graphics/color.hpp"

namespace sani {
	namespace graphics {

		Color::Color(const uint8 r, const uint8 g, const uint8 b, const uint8 a) : r(static_cast<float32>(r / 255.0f)),
																		     	   g(static_cast<float32>(g / 255.0f)),
																				   b(static_cast<float32>(b / 255.0f)),
																				   a(static_cast<float32>(a / 255.0f)) {
		}
		Color::Color(const Color& color, const uint8 a) : r(color.r),
														  g(color.g),
														  b(color.b),
														  a(static_cast<float32>(a / 255.0f)) {
		}

		Color::Color(const float32 r, const float32 g, const float32 b, const float32 a) : r(r),
																						   g(g),
																						   b(b),
																						   a(a) {
		}
		Color::Color(const Color& color, const float32 a) : r(color.r),
															g(color.g),
															b(color.b),
															a(static_cast<int8>(255 * a)) {
		}

		Color::Color() : Color(0.0f, 0.0f, 0.0f, 0.0f) {
		}

		Color::~Color() {
		}

		Color& Color::operator =(const Color& rhs) {
			r = rhs.r;
			g = rhs.g;
			b = rhs.b;
			a = rhs.a;
			
			return *this;
		}
		bool Color::operator ==(const Color& rhs) {
			return r == rhs.r &&
				   g == rhs.g &&
				   b == rhs.b &&
				   a == rhs.a;
		}
		bool Color::operator !=(const Color& rhs) {
			return !(*this == rhs);
		}

		const Color Color::white	= Color(1.0f, 1.0f, 1.0f, 1.0f);
		const Color Color::black	= Color(0.0f, 0.0f, 0.0f, 1.0f);
		const Color Color::red		= Color(1.0f, 0.0f, 0.0f, 1.0f);
		const Color Color::green	= Color(0.0f, 1.0f, 0.0f, 1.0f);
		const Color Color::blue		= Color(0.0f, 0.0f, 1.0f, 1.0f);
	}
}


