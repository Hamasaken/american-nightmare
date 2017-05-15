#version 400

// Input
in fData
{
    vec4 color;
	vec2 tex;
}frag;  

// Output
out vec4 outputColor;

// Uniforms
uniform sampler2D texture;

void main(void)
{
	vec4 textureColor = texture2D(texture, vec2(frag.tex.x, 1.f - frag.tex.y));
	if (textureColor.a < 0.15f)
		discard;

	outputColor = vec4(textureColor.r, textureColor.g, textureColor.b, frag.color.a);	
}

