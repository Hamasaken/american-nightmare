#version 440 core

layout(points) in;
layout(triangle_strip, max_vertices = 36) out;

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

void CreateVertex(mat4 rot, vec3 offset, vec2 tex)
{
	frag.color = vertices[0].color;
	frag.tex = tex;
	gl_Position = projection * view * world * ((gl_in[0].gl_Position + rot * vec4(offset.x, offset.y, offset.z, 0.0)));
    EmitVertex();
}

void main()
{
	float left		= -vertices[0].size.x;
	float right		= vertices[0].size.x;
	float top		= vertices[0].size.y;
	float bottom	= -vertices[0].size.y;
	float near		= vertices[0].size.x;
	float far		= -vertices[0].size.x;

	float r = vertices[0].rotation;
/*	mat4 rotationMatrix = { vec4(cos(r),	-sin(r),	0,			0),
							vec4(sin(r),	cos(r),		0,			0),
							vec4(0,			0,			1.f,		0),
							vec4(0,			0,			0,			1.f) }; */
	
	mat4 rotationMatrix = { vec4(cos(r),	-sin(r),	sin(r),		0),
							vec4(sin(r),	cos(r),		-sin(r),	0),
							vec4(-sin(r),	sin(r),		cos(r),		0),
							vec4(0,			0,			0,			1.f) };


	// FRONT
	CreateVertex(rotationMatrix, vec3(left, top, near), vec2(0, 1));
	CreateVertex(rotationMatrix, vec3(left, bottom, near), vec2(0, 0));
	CreateVertex(rotationMatrix, vec3(right, top, near), vec2(1, 1));
    EndPrimitive();
	CreateVertex(rotationMatrix, vec3(left, bottom, near), vec2(0, 0));
	CreateVertex(rotationMatrix, vec3(right, bottom, near), vec2(0, 1));
	CreateVertex(rotationMatrix, vec3(right, top, near), vec2(1, 1));
    EndPrimitive();

	// BACK
	CreateVertex(rotationMatrix, vec3(left, top, far), vec2(0, 1));
	CreateVertex(rotationMatrix, vec3(left, bottom, far), vec2(0, 0));
	CreateVertex(rotationMatrix, vec3(right, top, far), vec2(1, 1));
    EndPrimitive();
	CreateVertex(rotationMatrix, vec3(left, bottom, far), vec2(0, 0));
	CreateVertex(rotationMatrix, vec3(right, bottom, far), vec2(0, 1));
	CreateVertex(rotationMatrix, vec3(right, top, far), vec2(1, 1));
    EndPrimitive();

	// LEFT
	CreateVertex(rotationMatrix, vec3(left, top, far), vec2(0, 1));
	CreateVertex(rotationMatrix, vec3(left, top, near), vec2(0, 0));
	CreateVertex(rotationMatrix, vec3(left, bottom, far), vec2(1, 1));
    EndPrimitive();
	CreateVertex(rotationMatrix, vec3(left, top, near), vec2(0, 0));
	CreateVertex(rotationMatrix, vec3(left, bottom, near), vec2(0, 1));
	CreateVertex(rotationMatrix, vec3(left, bottom, far), vec2(1, 1));
    EndPrimitive();

	// RIGHT
	CreateVertex(rotationMatrix, vec3(right, top, far), vec2(0, 1));
	CreateVertex(rotationMatrix, vec3(right, bottom, far), vec2(1, 1));
	CreateVertex(rotationMatrix, vec3(right, top, near), vec2(0, 0));
    EndPrimitive();
	CreateVertex(rotationMatrix, vec3(right, top, near), vec2(0, 0));
	CreateVertex(rotationMatrix, vec3(right, bottom, far), vec2(1, 1));
	CreateVertex(rotationMatrix, vec3(right, bottom, near), vec2(0, 1));
    EndPrimitive();

	// TOP
	CreateVertex(rotationMatrix, vec3(left, top, far), vec2(0, 1));
	CreateVertex(rotationMatrix, vec3(right, top, far), vec2(1, 1));
	CreateVertex(rotationMatrix, vec3(left, top, near), vec2(0, 0));
    EndPrimitive();
	CreateVertex(rotationMatrix, vec3(right, top, far), vec2(1, 1));
	CreateVertex(rotationMatrix, vec3(right, top, near), vec2(0, 0));
	CreateVertex(rotationMatrix, vec3(left, top, near), vec2(0, 1));
    EndPrimitive();

	// BOTTOM
	CreateVertex(rotationMatrix, vec3(left, bottom, far), vec2(0, 1));
	CreateVertex(rotationMatrix, vec3(left, bottom, near), vec2(0, 0));
	CreateVertex(rotationMatrix, vec3(right, bottom, far), vec2(1, 1));
    EndPrimitive();
	CreateVertex(rotationMatrix, vec3(right, bottom, far), vec2(0, 0));
	CreateVertex(rotationMatrix, vec3(left, bottom, near), vec2(0, 1));
	CreateVertex(rotationMatrix, vec3(right, bottom, near), vec2(1, 1));
    EndPrimitive();
}