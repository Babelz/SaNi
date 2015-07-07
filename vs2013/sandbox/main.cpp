#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <windowsx.h>

#include "sani/platform/window.hpp"

using namespace sani::graphics;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	Window window(hInstance);
	
	window.initialize();
	
	return 0;
}