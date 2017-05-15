#version 400

layout(points) in;
layout(triangle_strip, max_vertices = 6) out;

// Input
in vData
{
    vec4 color;
	vec2 size;
	float rotation;
}vertices[];

// Output
out fData
{
    vec4 color;
	vec2 tex;
}frag;    

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	float left		= -vertices[0].size.x;
	float right		= vertices[0].size.x;
	float top		= vertices[0].size.y;
	float bottom	= -vertices[0].size.y;

	float r = vertices[0].rotation;
	mat4 rotationMatrix = { vec4(cos(r),	-sin(r),	0,			0),
							vec4(sin(r),	cos(r),		0,			0),
							vec4(0,			0,			1.f,		0),
							vec4(0,			0,			0,			1.f) };

	// Top left
	frag.color = vertices[0].color;
	frag.tex = vec2(0, 1);
	gl_Position = projection * view * world * rotationMatrix * (gl_in[0].gl_Position + vec4(left, top, 0.0, 0.0));
    EmitVertex();

	// Left Bottom
	frag.color = vertices[0].color;
	frag.tex = vec2(0, 0);
	gl_Position = projection * view * world * rotationMatrix * (gl_in[0].gl_Position + vec4(left, bottom, 0.0, 0.0));
    EmitVertex();

	// Right top
	frag.color = vertices[0].color;
	frag.tex = vec2(1, 1);
	gl_Position = projection * view * world * rotationMatrix * (gl_in[0].gl_Position + vec4(right, top, 0.0, 0.0));
    EmitVertex();

    EndPrimitive();

	// Left bootm
	frag.color = vertices[0].color;
	frag.tex = vec2(0, 0);
	gl_Position = projection * view * world * rotationMatrix * (gl_in[0].gl_Position + vec4(left, bottom, 0.0, 0.0));
    EmitVertex();

	// Bottom right
	frag.color = vertices[0].color;
	frag.tex = vec2(0, 1);
	gl_Position = projection * view * world * rotationMatrix * (gl_in[0].gl_Position + vec4(right, bottom, 0.0, 0.0));
    EmitVertex();

	// Right top
	frag.color = vertices[0].color;
	frag.tex = vec2(1, 1);
	gl_Position = projection * view * world * rotationMatrix * (gl_in[0].gl_Position + vec4(right, top, 0.0, 0.0));
    EmitVertex();

    EndPrimitive();
}