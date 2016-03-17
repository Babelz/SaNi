#pragma once

#include "sani/platform/platform_config.hpp"

namespace sani {

	namespace graphics {

		/*
			Default polygon shader sources.

			TODO: move to somewhere else when the content can load effects
			and the effect class has been implemented.
		*/

		/*
			TODO: as we have some major problems with AMD graphics adapters
			while the engine is running under GL 2.1, we just "force"
			the engine to use GL version 3.3 while running under Windows
			or Linux.

			Fix this by using the contents effects files so that there are
			GL 3.3 and 2.1 default effects.
		*/

		const char* const DefaultPolygonVertexSource =
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX || SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS
			"#version 330\n"
			""
			"layout(location = 0) in vec3 vertex_position;"
			"layout(location = 1) in vec4 vertex_color;"
			""
			"out vec4 out_vertex_color;"
			"uniform mat4 transform;"
#elif
			"#version 120\n"
			""
			"attribute vec3 vertex_position;"
			"attribute vec4 vertex_color;"
			""
			"varying vec4 out_vertex_color;"
			"uniform mat4 transform;"
#endif
			"void main() {"
			"	gl_Position = transform * vec4(vertex_position, 1.0);"
			"	out_vertex_color = vertex_color;"
			"}";

		const char* const DefaultPolygonFragmentSource =
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX || SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS
			"#version 330\n"
			""
			"in vec4 out_vertex_color;"
#elif
			"#version 120\n"
			""
			"varying vec4 out_vertex_color;"
#endif
			"void main() {"
			"  gl_FragColor = out_vertex_color;"
			"}";

		const char* const DefaultTexturedPolygonVertexSource =
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX || SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS
			"#version 330\n"
			""
			"layout(location = 0) in vec3 vertex_position;"
			"layout(location = 1) in vec4 vertex_color;"
			"layout(location = 2) in vec2 texture_coordinates;"
			""
			"out vec2 out_texture_coordinates;"
			"out vec4 out_vertex_color;"
			""
			"uniform mat4 transform;"
#elif
			"#version 120\n"
			""
			"attribute vec3 vertex_position;"
			"attribute vec4 vertex_color;"
			"attribute vec2 texture_coordinates;"
			""
			"varying vec2 out_texture_coordinates;"
			"varying vec4 out_vertex_color;"
			""
			"uniform mat4 transform;"
#endif
			"void main() {"
			"	gl_Position = transform * vec4(vertex_position, 1.0);"
			"	out_texture_coordinates = texture_coordinates;"
			"	out_vertex_color = vertex_color;"
			"}";

		const char* const DefaultTexturedPolygonFragmentSource =
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX || SANI_PLATFORM_WINDOWS
			"#version 330\n"
			""
			"in vec2 out_texture_coordinates;"
			"in vec4 out_vertex_color;"
			""
			"uniform sampler2D sampler;"
#elif
			"#version 120\n"
			""
			"varying vec2 out_texture_coordinates;"
			"varying vec4 out_vertex_color;"
			""
			"uniform sampler2D sampler;"
#endif
			"void main() {"
			"	gl_FragColor = texture2D(sampler, out_texture_coordinates) * out_vertex_color;"
			"}";
	}
}