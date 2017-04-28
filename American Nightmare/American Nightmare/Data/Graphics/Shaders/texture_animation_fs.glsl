#version 430

struct PointLight
{
	vec4 position;
	vec4 diffuse;
	vec4 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform int nrOfLights;
uniform PointLight pointLights[100];


// Input
in vec2 textureUV;
in vec3 position;
in vec3 normalw;

// Uniform
//uniform vec4 lightPos;
//uniform vec4 lightDiffuse;
uniform vec4 viewPos;

uniform sampler2D texture;
uniform sampler2D normal;

uniform bool isRight;

// Output
layout(location = 0) out vec4 fragment_color;

vec4 ads(vec4 lightPosition, vec4 lightDiffuse, vec3 inFragPos, vec3 inNormal, vec4 inTexDiffuse)
{
	vec3 normal = normalize(inNormal);

	vec3 lightDir = normalize(lightPosition.xyz - inFragPos);
	vec4 diffuseLight = inTexDiffuse * max(dot(normal, lightDir), 0.f);

	return inTexDiffuse * 0.f + diffuseLight * lightDiffuse;
}

void main(void)
{
	vec4 bufferColor = texture2D(texture, vec2(textureUV.x, 1.f - textureUV.y));
	vec3 bufferNormal = texture2D(normal, vec2(textureUV.x, 1.f - textureUV.y)).rgb;

	/*bufferNormal = mat3(vec3(cos(3.14/7.f), 0, sin(3.14/7.f)), 
		vec3(0, 1, 0),
		vec3(-sin(3.14/7.f), 0, cos(3.14/7.f))) * bufferNormal;
	
	if (!isRight)
		bufferNormal.x = bufferNormal.x * -1.f;*/

	//vec4 result = ads(lightPos, lightDiffuse, position, bufferNormal, bufferColor);
	//fragment_color = vec4(result.rgb, bufferColor.a);

	vec4 result = vec4(0);

	for(int i = 0; i < nrOfLights; i++)
	{
		result += ads(pointLights[i].position, pointLights[i].diffuse, position, normalw, bufferColor);	
	}

	fragment_color = vec4(result.rgb, bufferColor.a);

	//fragment_color = vec4(pointLights[1].position.xyz, bufferColor.a);

	//fragment_color = vec4(bufferNormal, bufferColor.a);
	//fragment_color = vec4(normalw, bufferColor.a);
}