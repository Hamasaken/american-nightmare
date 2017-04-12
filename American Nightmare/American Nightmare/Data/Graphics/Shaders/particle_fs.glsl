#version 400

// Input
in vec3 color;

// Output
out vec4 outputColor;

void main(void)
{
	// Setting color
	outputColor = vec4(color, 1.f);
}
