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
#include "sani/platform/graphics/texture.hpp"
using namespace sani::resource;
#include "sani/core/math/trigonometric.hpp"

#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/graphics/renderables/circle.hpp"

sani::resource::Texture2D* tuksu = nullptr;
ResourceManager* resourceManager = nullptr;
FileSystem* fileSystem = new FileSystem();

void initResource(GraphicsDevice* gdevice) {
	resourceManager = new ResourceManager(fileSystem, gdevice);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WIN32_ASSERT();

	Window window(hInstance, 1280, 720);
	window.initialize();
	window.show();

	WIN32_ASSERT();

	GraphicsDevice graphicsDevice(window.getHandle(), hInstance, 1280, 720);
	graphicsDevice.initialize();

	namespace sr = sani::resource;
	initResource(&graphicsDevice);
	tuksu = resourceManager->load<sr::Texture2D>("../../assets/tuksu.out");

	Buffer<float32> vertices(21, BufferSizing::Static);

	VertexPositionColor v1(Vec3f(32.0f, 0.0f, 0.0f), sani::graphics::color::red);
	VertexPositionColor v2(Vec3f(64.0f, 64.0f, 0.0f), sani::graphics::color::red);
	VertexPositionColor v3(Vec3f(0.0f, 64.0f, 0.0f), sani::graphics::color::red);

	VertexPositionColor vert[] = 
	{
		v1,
		v2,
		v3
	};

	vertices.push(reinterpret_cast<float32*>(vert), 21);

	char* vertexSource =
		"#version 330 core\n"
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

	char* fragmentSource =
		"#version 330 core\n"
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
	glGetError();
	Camera2D camera(graphicsDevice.getViewport());
	camera.computeTransformation();
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

	window.sizeChanged += SANI_EVENT_HANDLER(void(), ([&window, &graphicsDevice, &camera]() {
		Viewport viewport;

		viewport.width = window.getClientWidth();
		viewport.height = window.getClientHeight();
		
		graphicsDevice.setViewport(viewport);

		graphicsDevice.setBackBufferWidth(viewport.width);
		graphicsDevice.setBackBufferHeight(viewport.height);

		camera.setViewport(graphicsDevice.getViewport());
	}));

	sani::graphics::Triangle triangle(256, 256);
	triangle.fill = color::red;
	triangle.borderFill = Color(0.0f, 1.0f, 0.0f, 0.5f);
	triangle.transform.setPosition(600, 300);
	triangle.transform.setOrigin(128, 0);
	triangle.borderThickness = 32.0f;
	
	sani::graphics::Rectangle rectangle(600, 300, 400, 300);
	//rectangle.fill = Color(1.0f, 0.0f, 1.0f, 0.25f);
	rectangle.borderFill = Color(0.0f, 1.0f, 0.0f, 0.5f);
	rectangle.borderThickness = 16.0f;

	sani::graphics::Circle circle(0, 0, 100, 6);
	circle.borderThickness = 32.0f;
	recomputeGeometryData(circle);

	while (window.isOpen()) {
		if (graphicsDevice.hasErrors()) break;
	
		window.listen();

		camera.computeTransformation();
		sani::math::Mat4f transform = camera.transformation();
		graphicsDevice.setShaderUniform(program, "transform", (void*)&transform, UniformType::Mat4F);

		graphicsDevice.bindTexture(tuksu->getID());

		graphicsDevice.clear(0.0f, 0.0f, 0.0f, 1.0f);

		// Update..
		triangle.transform.rotate(0.01f);
		recomputeGeometryData(triangle);

		rectangle.transform.rotate(0.01f);
		recomputeGeometryData(rectangle);
		
		circle.transform.rotate(0.01f);
		circle.transform.move(1, 1);
		recomputeGeometryData(circle);

		// Render..
		renderer.beginRenderingIndexedPolygons(transform, 7, RenderMode::Triangles);
		render(rectangle, renderer);
		renderer.endRendering();
		
		renderer.beginRenderingPolygons(transform, 7, RenderMode::Triangles);
		render(triangle, renderer);
		renderer.endRendering();

		renderer.beginRenderingPolygons(transform, 7, RenderMode::TriangleFan);
		render(circle, renderer);
		renderer.endRendering();
		graphicsDevice.unbindTexture();
	}

	graphicsDevice.cleanUp();

	return 0;
}

#endif