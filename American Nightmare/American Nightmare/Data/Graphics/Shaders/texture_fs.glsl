#version 400

// Input
in vec2 textureUV;

uniform sampler2D texture;

// Output
out vec4 outputColor;

void main(void)
{
	// Setting color
	
	outputColor = texture2D(texture, vec2(textureUV.x, 1.f - textureUV.y));
}