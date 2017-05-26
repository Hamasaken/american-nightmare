#version 440 core

layout(location = 0) in vec3 inputPosition;

uniform mat4 world;

void main() {
	gl_Position = world * vec4(inputPosition, 1.f);
}