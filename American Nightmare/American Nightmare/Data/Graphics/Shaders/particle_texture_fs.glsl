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

// Uniforms
uniform sampler2D texture;

void main(void)
{
	vec4 textureColor = texture2D(texture, vec2(texture.x, 1.f - texture.y));
	vec4 color = texture2D(texture, vec2(texture.x, 1.f - texture.y));
	color = vec4(1, 1, 1, 1);

	outputColor = vec4(color.r, color.g, color.b, color.a);	
}

