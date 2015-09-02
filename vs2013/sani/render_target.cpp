#include "sani/platform/graphics_device.hpp"
#include "render_target.h"

namespace sani {
	namespace graphics {

		RenderTarget2D::RenderTarget2D(GraphicsDevice& device, const uint16 width, const uint16 height) : width(width),
																										  height(height) {
			initialize(device);
		}

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
		// Win32 OpenGL implementation.

		// TODO: add directx support.
#endif
	}
}