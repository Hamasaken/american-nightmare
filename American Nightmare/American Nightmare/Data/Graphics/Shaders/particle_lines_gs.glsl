#version 440 core

layout(points) in;
layout(line_strip, max_vertices = 2) out;

// Input
in vData
{
	vec3 position;
    vec4 color;
	vec2 size;
	float rotation;
}vertices[];

// Output
out fData
{
	vec3 position;
	vec3 center;
    vec4 color;
	vec2 size;
}frag;    

// Uniform
uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void CreateVertex(mat4 rot, vec4 color, vec3 position, vec2 offset, vec2 size)
{
	frag.color = color;
	frag.position = vec3(projection * view * world * (vec4(position + mat3(rot) * vec3(offset.x, offset.y, 0.0), 0)));
	frag.center = vec3(projection * view * world * vec4(position, 0));
	frag.size = size;
	
	gl_Position = projection * view * world * ((gl_in[0].gl_Position + rot * vec4(offset.x, offset.y, 0.0, 0.0)));
    EmitVertex();
}

void main()
{
	float left = -vertices[0].size.x;
	float right = vertices[0].size.x;

	float r = vertices[0].rotation;
	mat4 rotationMatrix = { vec4(cos(r),	-sin(r),	0,			0),
							vec4(sin(r),	cos(r),		0,			0),
							vec4(0,			0,			1.f,		0),
							vec4(0,			0,			0,			1.f) };

	CreateVertex(rotationMatrix, vertices[0].color, vertices[0].position, vec2(left, 0), vertices[0].size);
	CreateVertex(rotationMatrix, vertices[0].color, vertices[0].position, vec2(right, 0), vertices[0].size);
    EndPrimitive();
}