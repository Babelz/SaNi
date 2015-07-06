#include <windows.h>
#include <windowsx.h>

#include "sani/platform/platform_config.hpp"
#include "sani/platform/window.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

using namespace sani::graphics;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Window w(hInstance);
		

	return 0;
}

#elif 

int main() {
	return 0;
}

#endif