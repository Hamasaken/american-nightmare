#version 440 core

// Input
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec2 inputTextureUV;

// Output
out vec2 textureUV;

void main() {
	textureUV = inputTextureUV;
	gl_Position = vec4(inputPosition, 1.f);	
}