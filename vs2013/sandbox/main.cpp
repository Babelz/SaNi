#include <iostream>

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#pragma comment(lib, "OpenGL32.lib")

#include <Windows.h>

#include "sani/graphics/renderer.hpp"
#include "sani/graphics/color.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/window.hpp"
#include "sani/platform/graphics/viewport.hpp"
#include "sani/platform/graphics/render_target_2d.hpp"
#include "sani/debug.hpp"
#include "sani/graphics/camera2d.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/graphics/vertex_position_color.hpp"
#include "sani/core/math/vector.hpp"
#include "sani/graphics/renderables/triangle.hpp"
#include "sani/graphics/renderables/triangle.hpp"
#include <random>

using namespace sani::graphics;
using namespace sani::math;

#include "sani/platform/file/file_system.hpp"
#include "sani/platform/file/file_stream.hpp"
#include "sani/resource/resources.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/resource/effect.hpp"
using namespace sani::resource;
#include "sani/core/math/trigonometric.hpp"

#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/graphics/renderables/circle.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WIN32_ASSERT();

	Window window(hInstance, 1280, 720);
	window.initialize();
	window.show();

	WIN32_ASSERT();

	GraphicsDevice graphicsDevice(window.getHandle(), hInstance, 1280, 720);
	graphicsDevice.initialize();

	Camera2D camera(graphicsDevice.getViewport());
	camera.computeTransformation();
	FileSystem fileSystem;
	ResourceManager resources(&fileSystem, &graphicsDevice);
	Texture2D* tuksu = resources.load<Texture2D>("../../assets/tuksu.snb");
	volatile Effect* effect = resources.load<Effect>("../../assets/polygon.snb");

	window.sizeChanged += SANI_EVENT_HANDLER(void(), ([&window, &graphicsDevice, &camera]() {
		Viewport viewport;

		viewport.width = window.getClientWidth();
		viewport.height = window.getClientHeight();

		graphicsDevice.setViewport(viewport);

		graphicsDevice.setBackBufferWidth(viewport.width);
		graphicsDevice.setBackBufferHeight(viewport.height);

		camera.setViewport(graphicsDevice.getViewport());
	}));

	Renderer renderer(graphicsDevice);
	renderer.initialize();

	std::vector<Triangle*> triangles;

	for (size_t i = 0; i < 128; i++) {
		for (size_t j = 0; j < 128; j++) {
			Triangle* t = new Triangle(32.0f, 32.0f);
			t->transform.position.x = j * 32.0f;
			t->transform.position.y = i * 32.0f;
			t->fill = Color(rand() * 0.001f,
							rand() * 0.0001f,
							rand() * 0.00001f,
							0.75f);
			t->borderFill = Color(rand() * 0.001f,
								  rand() * 0.0001f,
								  rand() * 0.00001f,
								  1.0f);

			recomputeGeometryData(*t);

			triangles.push_back(t);
		}
	}

	while (window.isOpen()) {
		if (graphicsDevice.hasErrors()) break;

		// Update.
		window.listen();

		camera.computeTransformation();
		const sani::math::Mat4f transform = camera.transformation();

		graphicsDevice.clear(0.0f, 0.0f, 0.0f, 1.0f);
		
		for (Triangle* t : triangles) {
			t->transform.rotation += 0.1f;
			recomputeGeometryData(*t);
		} 

		renderer.beginRendering(transform);

		for (Triangle* t : triangles) renderer.renderElement(t);

		renderer.endRendering();
	}

	graphicsDevice.cleanUp();

	return 0;
}

#endif