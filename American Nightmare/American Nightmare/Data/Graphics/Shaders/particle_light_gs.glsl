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
	float size;
}frag;    

// Uniform
uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void CreateVertex(vec4 color, vec3 position, vec2 offset, vec2 size)
{
	frag.color = color;
	frag.position = vec3(projection * view * world * (vec4(position + vec3(offset.x, offset.y, 0.0), 0)));
	frag.center = vec3(projection * view * world * vec4(position, 0));
	frag.size = size.x;
	
	gl_Position = projection * view * world * ((gl_in[0].gl_Position + vec4(offset.x, offset.y, 0.0, 0.0)));
    EmitVertex();
}

void main()
{
	float left = -vertices[0].size.x;
	float right = vertices[0].size.x;
	float top = vertices[0].size.y;
	float bottom = -vertices[0].size.y;

	CreateVertex(vertices[0].color, vertices[0].position, vec2(left, top), vertices[0].size);
	CreateVertex(vertices[0].color, vertices[0].position, vec2(left, bottom), vertices[0].size);
	CreateVertex(vertices[0].color, vertices[0].position, vec2(right, top), vertices[0].size);
    EndPrimitive();

	CreateVertex(vertices[0].color, vertices[0].position, vec2(left, bottom), vertices[0].size);
	CreateVertex(vertices[0].color, vertices[0].position, vec2(right, bottom), vertices[0].size);
	CreateVertex(vertices[0].color, vertices[0].position, vec2(right, top), vertices[0].size);
    EndPrimitive();
}