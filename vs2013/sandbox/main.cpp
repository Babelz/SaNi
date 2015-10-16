#include <iostream>

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#pragma comment(lib, "OpenGL32.lib")

#include <Windows.h>

#include "sani/graphics/renderer.hpp"
#include "sani/platform/graphics/color.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/window.hpp"
#include "sani/debug.hpp"

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
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WIN32_ASSERT();

	Window window(hInstance, 800, 600);
	window.initialize();
	window.show();

	WIN32_ASSERT();

	GraphicsDevice graphicsDevice(window.getHandle(), hInstance, 800, 600);
	graphicsDevice.initialize();

	Vec3 v1(-1.0f, -1.0f, 0.0f);
	Vec3 v2(1.0f, -1.0f, 0.0f);
	Vec3 v3(0.0f, 1.0f, 0.0f);
	
	Vec3 vert[] =  {
		v1, v2, v3
	};

	Buffer vertexArray;
	graphicsDevice.generateVertexArray(vertexArray);
	graphicsDevice.bindVertexArray(vertexArray);

	Buffer vertexBuffer;
	graphicsDevice.generateBuffer(vertexBuffer);
	graphicsDevice.bindBuffer(vertexBuffer, BufferType::ArrayBuffer);
	graphicsDevice.setBufferData(vertexBuffer, BufferType::ArrayBuffer, sizeof(vert), &vert, BufferUsage::Static);

	VertexAttributeDescription desc;
	desc.location = 0;
	desc.elementsCount = 3;
	desc.type = Type::Float;
	desc.normalized = false;
	desc.stride = 0;
	desc.offset = 0;

	graphicsDevice.enableVertexAttributePointer(desc.location);
	graphicsDevice.createVertexAttributePointer(desc);

	while (window.isOpen()) {
		if (graphicsDevice.hasErrors()) break;
	
		window.listen();

		graphicsDevice.clear(Color::green);

		graphicsDevice.drawElements(0, 3);
	}

	graphicsDevice.cleanUp();

	return 0;
}

#endif