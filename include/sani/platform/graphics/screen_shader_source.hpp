#pragma once

namespace sani {

	namespace graphics {

		// Not sure if this does work with GLES, fix this or just dump Android...

		const char* const ScreenShaderVertexSource =
			"#version 330 core\n"
			"layout(location = 0) in vec2 position;"
			"layout(location = 1) in vec2 texCoords;\n"
			""
			"out vec2 TexCoords;"

			"void main()"
			"{"
			"	gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);"
			"	TexCoords = texCoords;"
			"}";

		const char* const ScreenShaderFragmentSource =
			"#version 330 core\n"
			"in vec2 TexCoords;"
			"out vec4 color;\n"
			""
			"uniform sampler2D screenTexture;"
			""
			"void main()"
			"{"
			"	gl_FragColor = texture2D(screenTexture, TexCoords);"
			"   //gl_FragColor = vec4(1, 0, 0, 1);\n"
			"}";
	}
}