#include <windows.h>
#include <windowsx.h>

#include "sani/platform/platform_config.hpp"
#include "sani/platform/window.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	sani::graphics::Window w(hInstance);
	w.initialize();

	return 0;
}