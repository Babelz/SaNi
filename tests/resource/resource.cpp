#include "catch/catch.hpp"
#include "sani/resource/resource_manager.hpp"
#include "sani/platform/file_system.hpp"
#include "sani/platform/platform_config.hpp"
#include "sani/platform/window.hpp"
#include "sani/platform/graphics_device.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include <Windows.h>

using namespace sani::resource;
using namespace sani::io;
using namespace sani::graphics;
FileSystem fs;
GraphicsDevice* device;
Window* window;
ResourceManager* manager;
TEST_CASE("Resource .png loading", "[resource]") {
	window = new Window(GetModuleHandle(NULL), 800, 600);
	window->initialize();
	device = new GraphicsDevice(window->getHandle(), GetModuleHandle(NULL), 800, 600);
	REQUIRE(device->initialize());
	manager = new ResourceManager(&fs, device);
	manager->load("../../assets/tuksu.png");

}


#endif