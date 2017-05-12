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
    vec4 color;
	vec2 tex;
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
	frag.tex = vec2(0, 1);
    gl_Position = gl_in[0].gl_Position + vec4(left, top, 0.0, 0.0);
    EmitVertex();

	// Left Bottom
	frag.color = vertices[0].color;
	frag.position = vertices[0].position + vec3(left, bottom, 0.0);
	frag.tex = vec2(0, 0);
	gl_Position = gl_in[0].gl_Position + vec4(left, bottom, 0.0, 0.0);
    EmitVertex();

	// Right top
	frag.color = vertices[0].color;
	frag.position = vertices[0].position + vec3(right, top, 0.0);
	frag.tex = vec2(1, 1);
    gl_Position = gl_in[0].gl_Position + vec4(right, top, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();

	// Left bootm
	frag.color = vertices[0].color;
	frag.position = vertices[0].position + vec3(left, bottom, 0.0);
	frag.tex = vec2(0, 0);
	gl_Position = gl_in[0].gl_Position + vec4(left, bottom, 0.0, 0.0);
    EmitVertex();

	// Bottom right
	frag.color = vertices[0].color;
	frag.position = vertices[0].position + vec3(right, bottom, 0.0);
	frag.tex = vec2(0, 1);
    gl_Position = gl_in[0].gl_Position + vec4(right, bottom, 0.0, 0.0);
    EmitVertex();

	// Right top
	frag.color = vertices[0].color;
	frag.position = vertices[0].position + vec3(right, top, 0.0);
	frag.tex = vec2(1, 1);
    gl_Position = gl_in[0].gl_Position + vec4(right, top, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}