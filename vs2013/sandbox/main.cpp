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

	window.sizeChanged += SANI_EVENT_HANDLER(void(), ([&window, &graphicsDevice, &camera]() {
		Viewport viewport;

		viewport.width = window.getClientWidth();
		viewport.height = window.getClientHeight();

		graphicsDevice.setViewport(viewport);

		graphicsDevice.setBackBufferWidth(viewport.width);
		graphicsDevice.setBackBufferHeight(viewport.height);

		camera.setViewport(graphicsDevice.getViewport());
	}));

	char* vertexSource = "#version 330 core\n"
		"layout(location = 0) in vec3 vertex_position;"
		"layout(location = 1) in vec4 color;"
		""
		"out vec4 out_color;"
		"uniform mat4 transform;"
		""
		"void main() {"
		""
		"	gl_Position = transform * vec4(vertex_position, 1.0);"
		"	out_color = color;"
		""
		"}";

	char* fragmentSource = "#version 330 core\n"
		"in vec4 out_color;"
		"out vec4 vertex_color;"
		""
		"void main(){"
		""
		"	vertex_color = out_color;"
		""
		"}";

	uint32 vertex = 0;
	uint32 fragment = 0;
	uint32 program = 0;

	graphicsDevice.compileShader(vertex, vertexSource, ShaderType::Vertex);
	assert(!graphicsDevice.hasErrors());

	graphicsDevice.compileShader(fragment, fragmentSource, ShaderType::Fragment);
	assert(!graphicsDevice.hasErrors());

	graphicsDevice.createProgram(program);
	graphicsDevice.linkToProgram(program, vertex, true);
	graphicsDevice.linkToProgram(program, fragment, true);
	graphicsDevice.linkProgram(program);
	graphicsDevice.useProgram(program);

	Renderer renderer(graphicsDevice);
	renderer.initialize();

	Triangle triangle(32, 32);

	while (window.isOpen()) {
		if (graphicsDevice.hasErrors()) break;

		// Update.
		window.listen();
		graphicsDevice.bindTexture(tuksu->getID());
		camera.computeTransformation();
		const sani::math::Mat4f transform = camera.transformation();
		graphicsDevice.setShaderUniform(program, "transform", (void*)&transform, UniformType::Mat4F);

		graphicsDevice.clear(0.0f, 0.0f, 0.0f, 1.0f);

		renderer.beginRendering(transform);

		float32 offx = 0.0f;
		float32 offy = 0.0f;

		for (uint32 i = 0; i < 3; i++) {
			offx = 0.0f;

			for (size_t j = 0; j < 3; j++) {
				triangle.transform.position.x = 300 + j * 32.0f + offx;
				triangle.transform.position.y = 300 + i * 32.0f + offy;

				triangle.borderThickness += 0.001f;
				triangle.transform.rotation += 0.0001f;
				triangle.transform.origin.x += 0.0001f;
				triangle.transform.origin.y += 0.0001f;
				triangle.borderFill.r = rand() * 0.0001f;
				triangle.borderFill.g = rand() * 0.00001f;
				triangle.borderFill.b = rand() * 0.000001f;

				recomputeGeometryData(triangle);
				updateRenderData(triangle);

				renderer.render(&triangle);

				offx += 32.0f;
			}

			offy += 32.0f;
		}

		static int a = 1;

		Circle c(100, a++);

		c.fill = color::green;
		c.transform.position.x += 300;
		c.transform.position.y += 300;

		recomputeGeometryData(c);
		updateRenderData(c);

		renderer.render(&c);

		renderer.endRendering();

	}

	graphicsDevice.cleanUp();

	return 0;
}

#endif