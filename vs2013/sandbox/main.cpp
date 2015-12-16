#include <iostream>

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#pragma comment(lib, "OpenGL32.lib")

#include <Windows.h>

#include "sani/engine/services/contracts/render_service_contract.hpp"
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
#include "sani/core/func.hpp"
#include "sani/graphics/renderables/triangle.hpp"
#include "sani/graphics/renderables/triangle.hpp"
#include <random>

#include "sani/platform/file/file_system.hpp"
#include "sani/platform/file/file_stream.hpp"
#include "sani/resource/resources.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/resource/effect.hpp"
#include "sani/core/math/trigonometric.hpp"

#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/graphics/renderables/circle.hpp"

#include "sani/engine/sani_engine.hpp"

using namespace sani::resource;
using namespace sani::graphics;
using namespace sani::math;
using namespace sani::engine;

void NO_ENGINE_MAIN(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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
	//volatile Effect* effect = resources.load<Effect>("../../assets/polygon.snb");

	window.sizeChanged += SANI_EVENT_HANDLER(void(), ([&window, &graphicsDevice, &camera]() {
		Viewport viewport;

		viewport.width = window.getClientWidth();
		viewport.height = window.getClientHeight();

		graphicsDevice.setViewport(viewport);

		graphicsDevice.setBackBufferWidth(viewport.width);
		graphicsDevice.setBackBufferHeight(viewport.height);

		camera.setViewport(graphicsDevice.getViewport());
	}));

	Renderer renderer(&graphicsDevice);
	renderer.initialize();

	std::vector<Triangle> triangles;

	for (uint32 i = 0; i < 3; i++) {
		for (uint32 j = 0; j < 3; j++) {

			Triangle t(128.0f, 128.0f);
			t.transform.position.x = j * 256.0f + 128.0f;
			t.transform.position.y = i * 256.0f + 128.0f;


			t.fill = Color(rand() * 0.001f,
				rand() * 0.0001f,
				rand() * 0.00001f,
				0.75f);

			t.borderFill = color::white;

			t.borderThickness = j == 0 ? 16.0f : 0.0f;
			t.texture = j == 1 ? tuksu : nullptr;

			if (t.texture != nullptr) t.fill = color::white;

			t.textureSource.h = 128.0f;
			t.textureSource.w = 128.0f;

			t.transform.origin.x = 16.0f;
			t.transform.origin.y = 0.0f;

			recomputeVertices(t);
			updateRenderData(t);

			triangles.push_back(t);
		}
	}

	std::vector<sani::graphics::Rectangle> rectangles;

	//for (uint32 i = 0; i < 3; i++) {
	//	for (uint32 j = 0; j < 3; j++) {
	sani::graphics::Rectangle r(0.0f, 0.0f, tuksu->getWidth(), tuksu->getHeight());
	//r.borderThickness = 8.0f;
	r.borderThickness = 16.0f;

	r.transform.origin.x = 0.0f;
	r.transform.origin.y = 0.0f;

	r.transform.position.x = 300.0f;
	r.transform.position.y = 100.0f;

	r.texture = tuksu;
	r.fill = color::white;
	r.textureSource = Rectf(0.0f, 0.0f, tuksu->getHeight(), tuksu->getWidth());

	recomputeVertices(r);
	updateRenderData(r);

	rectangles.push_back(r);
	//	}
	//}

	std::vector<Circle> circles;

	uint32 verticesCount = 4;

	for (uint32 i = 0; i < 3; i++) {
		Circle c(700.0f, 100.0f + i * 150.0f, 100.0f, verticesCount);

		c.borderThickness = 12.0f;

		if (i == 1) {
			c.fill.r = 0.0f;
			c.fill.g = 0.0f;
			c.fill.b = 0.0f;
			c.fill.a = 1.0f;
		}

		recomputeVertices(c);
		updateRenderData(c);

		verticesCount += 2;

		circles.push_back(c);
	}

	while (window.isOpen()) {
		if (graphicsDevice.hasErrors()) break;

		// Update.
		window.listen();

		camera.computeTransformation();
		const sani::math::Mat4f transform = camera.transformation();

		graphicsDevice.clear(0.0f, 0.0f, 0.0f, 1.0f);

		for (Triangle& t : triangles) {
			t.textureSource.x += 0.1f;
			t.transform.origin.x = t.localBounds.center().x;
			t.transform.origin.y = 0.0f;
			recomputeVertices(t);
			updateRenderData(t);
		}

		for (auto& r : rectangles) {
			recomputeVertices(r);
			updateRenderData(r);
		}

		renderer.beginRendering(transform);

		for (sani::graphics::Rectangle& r : rectangles) renderer.renderElement(&r);
//		renderer.renderElement(&rectangles[0]);

		for (Circle& c : circles) renderer.renderElement(&c);

		for (Triangle& t : triangles) renderer.renderElement(&t);

		renderer.endRendering();
	}

	graphicsDevice.cleanUp();
}
void ENGINE_MAIN(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SaNiEngine engine(hInstance);
	engine.start();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	NO_ENGINE_MAIN(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	
	//ENGINE_MAIN(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	return 0;
}

#endif