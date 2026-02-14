#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_color;

uniform mat4 model;

out vec4 vertColor;

void main() {
	gl_Position = model * vec4(a_pos, 1.0);
	vertColor = vec4(a_color, 1.0);
}
