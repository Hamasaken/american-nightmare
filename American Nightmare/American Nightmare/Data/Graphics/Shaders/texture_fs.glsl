#version 430

// Input
in vec2 textureUV;

uniform sampler2D texture;
uniform float alpha;

// Output
out vec4 outputColor;

void main(void)
{
	// Setting color
	outputColor = texture2D(texture, vec2(textureUV.x, 1.f - textureUV.y));

	// Just for text, don't remove
	if (alpha != -1)
	{
		outputColor.a = alpha;
	}
}