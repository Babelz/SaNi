#version 120
attribute vec3 in_position;
attribute vec4 in_color;

varying vec4 color;

uniform mat4 mvp;

void main() {
	gl_Position = mvp * vec4(in_position, 1.f);
	color = in_color;	
}