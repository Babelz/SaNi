#version 120

varying vec4 color;
varying vec2 uv;

uniform sampler2D tex;

void main() {
	vec4 texel = texture2D(tex, uv);
	gl_FragColor = color * texel; 
}