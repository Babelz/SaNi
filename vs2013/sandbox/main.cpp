#include <iostream>

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#pragma comment(lib, "OpenGL32.lib")

#include <Windows.h>

#include "sani/graphics/renderer.hpp"
#include "sani/platform/graphics/color.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/window.hpp"
#include "sani/platform/graphics/viewport.hpp"
#include "sani/platform/graphics/render_target_2d.hpp"
#include "sani/debug.hpp"
#include "sani/graphics/camera2d.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/core/math/vector.hpp"

using namespace sani::graphics;
using namespace sani::math;

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

	Vec3 v1(-0.5f, -0.5f, 0.0f);
	Vec3 v2(0.5f, -0.5f, 0.0f);
	Vec3 v3(0.5f, 0.5f, 0.0f);
	
	Vec3 v4(0.5f, 0.5f, 0.0f);
	Vec3 v5(-0.5f, 0.5f, 0.0f);
	Vec3 v6(-0.5f, -0.5f, 0.0f);

	Vec3 color(1.0f, 0.0f, 1.0f);

	Vec3 vert[] =  {
		v1, Vec3(1, 0, 0),
		v2, Vec3(0, 1, 0),
		v3, Vec3(1, 0, 0),
		v4, Vec3(0, 0, 1),
		v5, Vec3(1, 0, 0),
		v6, Vec3(1, 1, 0)
	};

	Buffer<float32> vertices(36, BufferSizing::Static);
	vertices.push(reinterpret_cast<float32*>(vert), 36);

	char* vertexSource =
		"#version 330 core\n"
		"layout(location = 0) in vec3 vertex_position;"
		"layout(location = 1) in vec3 color;"
		"out vec3 out_color;"
		"uniform mat4 transform;"
		"void main() {"
		""
		"	gl_Position = transform * vec4(vertex_position, 1.0);"
		"	out_color = color;"
		"}";

	char* fragmentSource =
		"#version 330 core\n"
		"in vec3 out_color;"
		"out vec3 vertex_color;"
		"void main(){"
		"vertex_color = out_color;"
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

	camera.setZoom(1.0f);

	while (window.isOpen()) {
		if (graphicsDevice.hasErrors()) break;
	
		window.listen();

		camera.computeTransformation();
		sani::math::Mat4f transform = camera.transformation();
		graphicsDevice.setShaderUniform(program, "transform", (void*)&transform, UniformType::Mat4F);

		graphicsDevice.clear(Color::black);
		
		renderer.beginRenderingUserPrimitives(transform, 6, RenderMode::Triangles);

		renderer.renderUserPrimitives(vertices);

		renderer.endRendering();

		camera.setX(-(graphicsDevice.getViewport().width / 2.0f));
		camera.setY(-(graphicsDevice.getViewport().height / 2.0f));
		camera.rotateBy(0.001f);
	}

	graphicsDevice.cleanUp();

	return 0;
}

#endif