#version 440 core

layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec2 inputUV;

uniform mat4 lightSpaceMatrix;
uniform mat4 world;

uniform vec2 uvTopLeft;
uniform vec2 uvTopRight;
uniform vec2 uvBotLeft;
uniform vec2 uvBotRight;
uniform bool isRight;

out vec2 textureUV;

void main() {

	if(inputPosition.x == -0.5f && inputPosition.y == 0.5f)
	{
		if(isRight)
			textureUV = uvTopLeft;
		else
			textureUV = uvTopRight;
	}
	else if(inputPosition.x == 0.5f && inputPosition.y == 0.5f)
	{
		if(isRight)
			textureUV = uvTopRight;
		else
			textureUV = uvTopLeft;
	}
	else if(inputPosition.x == -0.5f && inputPosition.y == -0.5f)
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

	gl_Position = lightSpaceMatrix * world * vec4(inputPosition, 1.f);
}