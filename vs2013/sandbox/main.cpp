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

using namespace sani::graphics;

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

	Buffer vertexArray;
	graphicsDevice.generateVertexArray(vertexArray);
	graphicsDevice.bindVertexArray(vertexArray);

	Buffer vertexBuffer;
	graphicsDevice.generateBuffer(vertexBuffer);
	graphicsDevice.bindBuffer(vertexBuffer, BufferType::ArrayBuffer);
	graphicsDevice.setBufferData(vertexBuffer, BufferType::ArrayBuffer, sizeof(vert), &vert, BufferUsage::Static);

	VertexAttributePointerDescription desc;
	desc.location = 0;
	desc.count = 3;
	desc.type = PrimitiveType::Float;
	desc.normalized = false;
	desc.stride = sizeof(float) * 6;
	desc.offset = 0;

	VertexAttributePointerDescription colorDesc;
	colorDesc.location = 1;
	colorDesc.count = 3;
	colorDesc.type = PrimitiveType::Float;
	colorDesc.normalized = false;
	colorDesc.stride = sizeof(float) * 6;
	colorDesc.offset = sizeof(float) * 3;

	graphicsDevice.createVertexAttributePointer(desc);
	assert(!graphicsDevice.hasErrors());

	graphicsDevice.createVertexAttributePointer(colorDesc);
	assert(!graphicsDevice.hasErrors());

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

	Shader vertex = 0;
	Shader fragment = 0;
	Shader program = 0;

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

	window.sizeChanged += SANI_EVENT_HANDLER(void(), ([&window, &graphicsDevice, &camera]() {
		Viewport viewport;

		viewport.width = window.getClientWidth();
		viewport.height = window.getClientHeight();
		
		graphicsDevice.setViewport(viewport);

		graphicsDevice.setBackBufferWidth(viewport.width);
		graphicsDevice.setBackBufferHeight(viewport.height);

		camera.setViewport(graphicsDevice.getViewport());
	}));

	camera.zoom.x = 1.0f;
	camera.zoom.y = 1.0f;
	camera.zoom.z = 1.0f;
	camera.rotation = 0.0f;

	while (window.isOpen()) {
		if (graphicsDevice.hasErrors()) break;
	
		window.listen();

		graphicsDevice.clear(Color::black);

		graphicsDevice.drawArrays(RenderMode::Triangles, 0, 6);

		camera.computeTransformation();
		sani::math::Mat4f transform = camera.transformation();
		graphicsDevice.setShaderUniform(program, "transform", (void*)&transform, UniformType::Mat4F);
		
		camera.position.x += 0.1f;
		camera.position.y += 0.1f;
	}

	graphicsDevice.cleanUp();

	return 0;
}

#endif