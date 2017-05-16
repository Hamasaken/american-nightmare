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

void CreateVertex(mat4 rot, vec2 offset, vec2 tex)
{
	frag.color = vertices[0].color;
	frag.tex = tex;
	gl_Position = projection * view * world * ((gl_in[0].gl_Position + rot * vec4(offset.x, offset.y, 0.0, 0.0)));
    EmitVertex();
}

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
	CreateVertex(rotationMatrix, vec2(left, top), vec2(0, 1));
	CreateVertex(rotationMatrix, vec2(left, bottom), vec2(0, 0));
	CreateVertex(rotationMatrix, vec2(right, top), vec2(1, 1));
    EndPrimitive();

	CreateVertex(rotationMatrix, vec2(left, bottom), vec2(0, 0));
	CreateVertex(rotationMatrix, vec2(right, bottom), vec2(0, 1));
	CreateVertex(rotationMatrix, vec2(right, top), vec2(1, 1));
    EndPrimitive();
}