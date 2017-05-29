#version 440 core

// Input
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec4 inputColor;
layout(location = 2) in vec2 inputSize;
layout(location = 3) in float inputRotation;

// Output
out vData
{
	vec3 position;
    vec4 color;
	vec2 size;
	float rotation;
}vertex;

void main(void)
{
	// Setting color + size + middle position
	vertex.color = inputColor;
	vertex.size = inputSize;
	vertex.rotation = inputRotation;
	vertex.position = inputPosition;

	// Setting vertex position according to matrices
	gl_Position = vec4(inputPosition, 1.f);
}