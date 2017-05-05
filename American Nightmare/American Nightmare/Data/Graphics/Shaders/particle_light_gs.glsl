#version 400

layout(points) in;
layout(triangle_strip, max_vertices = 6) out;

// Input
in vData
{
	vec3 position;
    vec4 color;
	vec2 size;
}vertices[];

// Output
out fData
{
	vec3 position;
	vec3 center;
    vec4 color;
}frag;    


void main()
{
	float left = -vertices[0].size.x;
	float right = vertices[0].size.x;
	float top = vertices[0].size.y;
	float bottom = -vertices[0].size.y;

	// Top left
	frag.color = vertices[0].color;
	frag.position = vertices[0].position + vec3(left, top, 0.0);
	frag.center = gl_in[0].gl_Position.xyz;
    gl_Position = gl_in[0].gl_Position + vec4(left, top, 0.0, 0.0);
    EmitVertex();

	// Top right
	frag.color = vertices[0].color;
	frag.position = vertices[0].position + vec3(right, top, 0.0);
	frag.center = gl_in[0].gl_Position.xyz;
    gl_Position = gl_in[0].gl_Position + vec4(right, top, 0.0, 0.0);
    EmitVertex();

	// Bottom left
	frag.color = vertices[0].color;
	frag.position = vertices[0].position + vec3(left, bottom, 0.0);
	frag.center = gl_in[0].gl_Position.xyz;
	gl_Position = gl_in[0].gl_Position + vec4(left, bottom, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();

	// Bottom left
	frag.color = vertices[0].color;
	frag.position = vertices[0].position + vec3(left, bottom, 0.0);
	frag.center = gl_in[0].gl_Position.xyz;
	gl_Position = gl_in[0].gl_Position + vec4(left, bottom, 0.0, 0.0);
    EmitVertex();

	// Top right
	frag.color = vertices[0].color;
	frag.position = vertices[0].position + vec3(right, top, 0.0);
	frag.center = gl_in[0].gl_Position.xyz;
    gl_Position = gl_in[0].gl_Position + vec4(right, top, 0.0, 0.0);
    EmitVertex();

	// Bottom right
	frag.color = vertices[0].color;
	frag.position = vertices[0].position + vec3(right, bottom, 0.0);
	frag.center = gl_in[0].gl_Position.xyz;
    gl_Position = gl_in[0].gl_Position + vec4(right, bottom, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}