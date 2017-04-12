#version 400

// Input
in vec3 inputPosition;
in vec2 inputColor;

// Output
out vec3 color;

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
	gl_Position = view * gl_Position;
	gl_Position = projection * gl_Position;
}