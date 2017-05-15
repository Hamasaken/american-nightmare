#version 400

// Input
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec4 inputColor;
layout(location = 2) in vec2 inputSize;

// Output
out vData
{
	vec3 position;
    vec4 color;
	vec2 size;
}vertex;

// Uniform
uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
	// Setting color + size + middle position
	vertex.color = inputColor;
	vertex.size = inputSize;
	vertex.position = vec3(projection * view* world * vec4(inputPosition, 1.f));

	// Setting vertex position according to matrices
	gl_Position = projection * view * world * vec4(inputPosition, 1.f);
}