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
	vec4 textureColor = texture2D(texture, vec2(textureUV.x, 1.f - textureUV.y));
	vec4 color = texture2D(texture, vec2(textureUV.x, 1.f - textureUV.y));
	color = vec4(1, 1, 1, 1);

	outputColor = vec4(color.r, color.g, color.b, color.a);	
}

