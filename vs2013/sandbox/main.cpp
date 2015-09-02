#include <iostream>

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#pragma comment(lib, "OpenGL32.lib")

#include <Windows.h>

#include "sani/platform/color.hpp"
#include "sani/platform/graphics_device.hpp"
#include "sani/platform/window.hpp"
#include "sani/assert.hpp"

using namespace sani::graphics;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WIN32_ASSERT();

	Window window(hInstance);
	window.initialize();
	window.show();

	GraphicsDevice graphicsDevice(window.getHandle(), hInstance);
	graphicsDevice.initialize();

	while (window.isOpen()) {
		window.listen();

		graphicsDevice.present();

		graphicsDevice.clear(Color::green);
	}

	graphicsDevice.cleanUp();

	return 0;
}

#endif