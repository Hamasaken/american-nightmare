#version 400

// Input
in fData
{
	vec3 position;
	vec3 center;
    vec4 color;
}frag;  

// Output
out vec4 outputColor;

void main(void)
{
	// Setting 
	float distance = distance(frag.position.xy, frag.center.xy);
	if (distance > 15)
	{
		outputColor = vec4(1.f, 1.f, 1.f, frag.color.a);
	}
	else
	{
		outputColor = vec4(1.f, 0.f, 1.f, frag.color.a);	
	}
}
