#include <iostream>

#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/platform/window.hpp"
#include "sani/assert.hpp"

#include <Windows.h>
#include <windowsx.h>

using namespace sani::graphics;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WIN32_ASSERT();

	Window w(hInstance);
	w.initialize();

	WIN32_ASSERT();

	w.show();

	w.setX(100);
	w.setY(100);

	w.setWidth(1920);
	w.setHeight(800);
	w.setSize(800, 600);

	w.setX(100);
	w.setY(100);
	w.setPosition(300, 300);

	w.setTitle("JEESUKSEN VITTU JA JOO JAAJOO");

	w.minimize();

	std::cout << "MINIMIZE" << std::endl;

	Sleep(1000);

	std::cout << "SHOW" << std::endl;

	w.show();

	while (w.isOpen()) {
		w.listen();
	}

	return 0;
}

#endif