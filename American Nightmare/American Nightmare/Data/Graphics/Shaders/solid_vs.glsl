#version 440 core

// Input
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputColor;

// Output
out vec3 color;

// Uniform
uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
	// Setting color
	color = inputColor;

	// Setting vertex position according to matrices
	gl_Position = world * vec4(inputPosition, 1.f);
	gl_Position = view * gl_Position;
	gl_Position = projection * gl_Position;
}