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

//Texture2D* tuksu = nullptr;
//ResourceManager* resourceManager = nullptr;
//FileSystem* fileSystem = new FileSystem();
//
//void initResource(GraphicsDevice* gdevice) {
//	resourceManager = new ResourceManager(fileSystem, gdevice);
//}

/*
	To test if our window, context etc even work.
*/
void glDraw() {
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// Draw the triangle !
	//glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WIN32_ASSERT();

	Window window(hInstance, 1280, 720);
	window.initialize();
	window.show();

	WIN32_ASSERT();

	GraphicsDevice graphicsDevice(window.getHandle(), hInstance, 1280, 720);
	graphicsDevice.initialize();

	//initResource(&graphicsDevice);
	//tuksu = static_cast<Texture2D*>(resourceManager->load("../../assets/tuksu.out"));

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

	sani::graphics::Triangle triangle(300, 300);
	triangle.transform.position = Vec3f(300, 300, 1);
	triangle.transform.origin = Vec3f(150, 0, 1);
	triangle.borderThickness = 32.0f;
	
	sani::graphics::Rectangle rectangle(600, 300, 64, 64);
	rectangle.fill = Color(1.0f, 0.0f, 1.0f, 0.25f);
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

		graphicsDevice.clear(0.0f, 0.0f, 0.0f, 1.0f);

		// Update..
		triangle.transform.rotation += 0.01f;
		recomputeGeometryData(triangle);
		updateRenderData(triangle);

		//rectangle.transform.rotation += 0.01f;
		recomputeGeometryData(rectangle);
		
		circle.transform.rotation += 0.01f;
		circle.transform.position.x += 1;
		circle.transform.position.y += 1;
		recomputeGeometryData(circle);

		// Render..
		renderer.beginRenderingIndexedPolygons(transform, 7, RenderMode::Triangles);
		render(rectangle, renderer);
		renderer.endRendering();

		renderer.beginRenderingPolygons(transform, 7, RenderMode::Triangles);
		
		for (uint32 i = 0; i < triangle.renderData.renderElementsCount; i++) {
			const uint32 index = triangle.renderData.renderElementIndices[i];
			const RenderElementData& renderElement = triangle.renderData.renderElements[index];
			
			const uint32 first			= renderElement.first;
			const uint32 last			= renderElement.last;
			const uint32 vertexElements = renderElement.vertexElements;
			const uint32 offset			= renderElement.offset;
			const float32* vertexData	= reinterpret_cast<float32*>(triangle.renderData.vertices.data());

			for (uint32 j = first; j < last + 1; j++) {
				renderer.renderPolygons(vertexData, vertexElements, j * (vertexElements + offset));
			}
		}

		renderer.endRendering();

		renderer.beginRenderingPolygons(transform, 7, RenderMode::TriangleFan);
		render(circle, renderer);
		renderer.endRendering();
	}

	graphicsDevice.cleanUp();

	return 0;
}

#endif