#version 400

// Input
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec2 inputTextureUV;

// Output
out vec2 textureUV;

// Uniform
uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
	// Setting color
	textureUV = inputTextureUV;

	// Setting vertex position according to matrices
	gl_Position = world * vec4(inputPosition, 1.f);
}