#pragma once
#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include "sani/platform/base_graphics_device.hpp"
#include <windows.h>

namespace sani {
	namespace graphics {

		/// @class GraphicsDeviceDX graphics_device_dx.hpp "sani/platform/graphics/graphics_device_dx.hpp"
		/// @author voidbab
		///
		/// DirectX (11) graphics device implementation. Mainly used with Windows systems.
		/// For OpenGL/ES devices, see "graphics_device_opengl.hpp" and "graphics_device_opengles.hpp".
		class GraphicsDeviceDX : public BaseGraphicsDevice {
		private:

		protected:
			virtual bool platformInitialize() const override;
		public:
			GraphicsDeviceDX(const uint32 screenWidth, const int32 screenHeight, const HINSTANCE hInstance);

			virtual const Window& getWindow() const;

			virtual ~GraphicsDeviceDX() override;
		};
	}
}

#endif