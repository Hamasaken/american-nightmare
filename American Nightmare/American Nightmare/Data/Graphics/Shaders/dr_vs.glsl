#version 430 core

// Input
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec2 inputTextureUV;
layout(location = 2) in vec3 inputNormal;

// Output
out vec3 position;
out vec2 textureUV;
out vec3 normal;

// Uniform
uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main() {
	position = vec3(world * vec4(inputPosition, 1.f));
	textureUV = inputTextureUV;
	normal = vec3(world * vec4(inputNormal, 1.f));
	gl_Position = projection * view * world * vec4(inputPosition, 1.f);
}