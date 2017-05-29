#version 440 core

// Input
in fData
{
	vec3 position;
	vec3 center;
    vec4 color;
	vec2 size;
}frag;  

// Output
out vec4 outputColor;

void main(void)
{
	vec4 color = frag.color;	

	float distance = abs(distance(frag.position.xy, frag.center.xy));
	outputColor = vec4(color.r, color.g, color.b, -0.40 + color.a / (2.f * distance / (frag.size)));	
}

