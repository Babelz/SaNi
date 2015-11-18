#version 120
attribute vec3 in_position;
attribute vec4 in_color;
attribute vec2 in_uv;

varying vec4 color;
varying vec2 uv;
uniform mat4 mvp;

void main() {
	gl_Position = mvp * vec4(in_position, 1.f);
	color = in_color;	
	uv = in_uv;
}