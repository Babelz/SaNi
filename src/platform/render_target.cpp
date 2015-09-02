#include "sani/platform/graphics_device.hpp"
#include "sani/platform/render_target.h"

namespace sani {
	namespace graphics {

		RenderTarget2D::RenderTarget2D(GraphicsDevice& device, const uint16 width, const uint16 height) : width(width),
																										  height(height),
																										  frameBuffer(0),
																										  stencilBuffer(0),
																										  colorBuffer(0),
																										  depthBuffer(0) {
			initialize(device);
		}

		uint16 RenderTarget2D::getWidth() const {
			return width;
		}
		uint16 RenderTarget2D::getHeight() const {
			return height;
		}

		uint32 RenderTarget2D::getStencilBuffer() const {
			return stencilBuffer;
		}
		uint32 RenderTarget2D::getColorBuffer() const {
			return colorBuffer;
		}
		uint32 RenderTarget2D::getDepthBuffer() const {
			return depthBuffer;
		}
		
		// Init functions per platform and API.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
		// Win32 OpenGL implementation.

		// TODO: add directx support.

		void RenderTarget2D::initialize(GraphicsDevice& device) {
			// Create OpenGL RenderTarget2D.
		}
#endif
	}
}