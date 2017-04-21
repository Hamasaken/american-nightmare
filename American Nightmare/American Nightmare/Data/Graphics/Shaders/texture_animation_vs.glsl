#version 430

// Input
in vec3 inputPosition;
in vec2 inputTextureUV;
in vec3 inputNormal;

// Output
out vec2 textureUV;
out vec3 position;
out vec3 normalw;

// Uniform
uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 uvTopLeft;
uniform vec2 uvTopRight;
uniform vec2 uvBotLeft;
uniform vec2 uvBotRight;
uniform bool isRight;

void main(void)
{
	if(inputPosition.x == -1.f && inputPosition.y == 1.f)
	{
		if(isRight)
			textureUV = uvTopLeft;
		else
			textureUV = uvTopRight;
	}
	else if(inputPosition.x == 1.f && inputPosition.y == 1.f)
	{
		if(isRight)
			textureUV = uvTopRight;
		else
			textureUV = uvTopLeft;
	}
	else if(inputPosition.x == -1.f && inputPosition.y == -1.f)
	{
		if(isRight)
			textureUV = uvBotLeft;
		else
			textureUV = uvBotRight;
	}
	else
	{
		if(isRight)
			textureUV = uvBotRight;
		else
			textureUV = uvBotLeft;
	}

	// Setting vertex position according to matrices
	position = vec3(world * vec4(inputPosition, 1.f));
	normalw = vec3(world * vec4(inputNormal, 1.f));
	gl_Position = projection * view * world * vec4(inputPosition, 1.f);
}