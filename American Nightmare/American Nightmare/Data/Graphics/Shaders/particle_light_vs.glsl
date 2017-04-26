#version 400

// Input
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec4 inputColor;

// Output
out vData
{
	vec3 position;
    vec4 color;
}vertex;

// Uniform
uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
	// Setting color
	vertex.color = inputColor;
	vertex.position = vec3(world * vec4(inputPosition, 1.f));

	// Setting vertex position according to matrices
	gl_Position = projection * view * world * vec4(inputPosition, 1.f);
}