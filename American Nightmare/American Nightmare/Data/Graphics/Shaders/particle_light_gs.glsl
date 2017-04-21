#version 400

layout(points) in;
layout(triangle_strip, max_vertices = 6) out;

// Input
in vData
{
    vec4 color;
}vertices[];

// Output
out fData
{
	vec3 center;
    vec4 color;
}frag;    


void main()
{
	
	float left = -0.01;
	float right = 0.01;
	float top = 0.01;
	float bottom = -0.01;

	// Top left
	frag.color = vertices[0].color;
	frag.center = gl_in[0].gl_Position.xyz;
    gl_Position = gl_in[0].gl_Position + vec4(left, top, 0.0, 0.0);
    EmitVertex();

	// Top right
	frag.color = vertices[0].color;
	frag.center = gl_in[0].gl_Position.xyz;
    gl_Position = gl_in[0].gl_Position + vec4(right, top, 0.0, 0.0);
    EmitVertex();

	// Bottom left
	frag.color = vertices[0].color;
	frag.center = gl_in[0].gl_Position.xyz;
	gl_Position = gl_in[0].gl_Position + vec4(left, bottom, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();

	// Bottom left
	frag.color = vertices[0].color;
	frag.center = gl_in[0].gl_Position.xyz;
	gl_Position = gl_in[0].gl_Position + vec4(left, bottom, 0.0, 0.0);
    EmitVertex();

	// Top right
	frag.color = vertices[0].color;
	frag.center = gl_in[0].gl_Position.xyz;
    gl_Position = gl_in[0].gl_Position + vec4(right, top, 0.0, 0.0);
    EmitVertex();

	// Bottom right
	frag.color = vertices[0].color;
	frag.center = gl_in[0].gl_Position.xyz;
    gl_Position = gl_in[0].gl_Position + vec4(right, bottom, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}