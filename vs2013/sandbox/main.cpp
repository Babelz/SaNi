#include <iostream>

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#pragma comment(lib, "OpenGL32.lib")

#include <Windows.h>

#include "sani/platform/graphics/color.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/window.hpp"
#include "sani/debug.hpp"

using namespace sani::graphics;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WIN32_ASSERT();

	Window window(hInstance, 800, 600);
	window.initialize();
	window.show();

	WIN32_ASSERT();

	GraphicsDevice graphicsDevice(window.getHandle(), hInstance, 800, 600);
	graphicsDevice.initialize();

	Color color = Color::green;

	while (window.isOpen()) {
		window.listen();

		color.r -= 0.01f;
		color.g += 0.01f;
		color.b -= 0.01f;
		color.a += 0.01f;

		graphicsDevice.clear(color);
	}

	graphicsDevice.cleanUp();

	return 0;
}

#endif