#include <iostream>

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/platform/graphics_device.hpp"
#include "sani/platform/window.hpp"
#include "sani/assert.hpp"

using namespace sani::graphics;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WIN32_ASSERT();

	Window w(hInstance);
	w.initialize();

	WIN32_ASSERT();

	w.show();

	HWND hwnd = w.getHandle();
	GraphicsDevice g(hwnd, hInstance);

	while (w.isOpen()) {
		w.listen();
	}

	return 0;
}

#endif