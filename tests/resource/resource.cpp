#include "catch/catch.hpp"
#include "sani/resource/resource_manager.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/platform/platform_config.hpp"
#include "sani/platform/graphics/window.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/resource/compiler/texture2d_writer.hpp"
#include "sani/resource/processor/texture2d_processor.hpp"
#include "sani/resource/pipeline/texture2d_importer.hpp"
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
	CHECK(device->initialize());
	manager = new ResourceManager(&fs, device);
	manager->load("../../assets/tuksu.png");

}

TEST_CASE("Resource deserialization compile time constants", "[resource]") {
	CHECK(DeserializableWith<sani::resource::Texture2DContent>::value() == "sani::resource::reader::Texture2DReader");

}


#endif