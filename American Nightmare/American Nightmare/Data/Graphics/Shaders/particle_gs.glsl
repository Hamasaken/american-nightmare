#version 400

layout(points) in;
layout(triangle_strip, max_vertices = 3) out;

// Input
in vData
{
    vec4 color;
}vertices[];

// Output
out fData
{
    vec4 color;
}frag;    


void main()
{
	frag.color = vertices[0].color;
    gl_Position = gl_in[0].gl_Position + vec4(0.0, 0.02, 0.0, 0.0);
    EmitVertex();

	frag.color = vertices[0].color;
    gl_Position = gl_in[0].gl_Position + vec4(0.01, 0.0, 0.0, 0.0);
    EmitVertex();

	frag.color = vertices[0].color;
	gl_Position = gl_in[0].gl_Position + vec4(-0.01, 0.0, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}