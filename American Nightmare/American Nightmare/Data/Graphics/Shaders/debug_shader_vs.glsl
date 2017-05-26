#version 440 core

layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec2 inputUV;

uniform mat4 world;

out vec2 textureUV;

void main() {
	textureUV = inputUV;
	gl_Position = world * vec4(inputPosition, 1.f);
}