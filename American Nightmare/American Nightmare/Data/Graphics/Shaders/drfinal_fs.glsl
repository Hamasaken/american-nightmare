#version 430 core

struct PointLight
{
	vec4 position;
	vec4 diffuse;
	vec4 specular;

	float strength;
	float constant;
	float linear;
	float quadratic;
	float radius;
};

// Uniform
uniform int nrOfLights;
uniform PointLight pointLights[100];

uniform vec4 viewPos;

uniform sampler2D drPosition;
uniform sampler2D drNormal;
uniform sampler2D drAmbient;
uniform sampler2D drDiffuse;
uniform sampler2D drSpecular;

in vec2 textureUV;

layout(location = 0) out vec4 fragment_color;

vec4 lightCalc(vec4 lightPosition, vec4 lightDiffuse, float strength, float lightConstant, float lightLinear, float lightQuadratic, vec3 inFragPos, vec3 inNormal, vec4 inDiffuse, vec4 inSpecular, float inDistance) 
{
	vec3 normal = normalize(inNormal);

	vec3 lightDir = normalize(lightPosition.xyz - inFragPos);
	vec4 diffuseLight = inDiffuse * max(dot(normal, lightDir), 0.f);

	vec3 viewDir = normalize(viewPos.xyz - inFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float specular = pow(max(dot(viewDir, reflectDir), 0.f), 32);
	vec4 specularLight = specular * inSpecular;

	float attenuation = 1.0 / (1.0 + lightLinear * inDistance + lightQuadratic * inDistance * inDistance);

	return strength * (diffuseLight * lightDiffuse * attenuation + specularLight * 0.2 * attenuation);
}

void main () {

	vec3 fragPos = texture2D(drPosition, textureUV).rgb;
    vec3 bufferNormal = texture2D(drNormal, textureUV).rgb;
    vec4 bufferAmb = texture2D(drAmbient, textureUV);
	vec4 bufferDif = texture2D(drDiffuse, textureUV);
    vec4 bufferSpec = texture2D(drSpecular, textureUV);

	vec4 result = vec4(0);

	result += bufferAmb * 0.3f;

	for(int i = 0; i < nrOfLights; i++)
	{
		float distance = length(pointLights[i].position.xyz - fragPos);

		if(distance < pointLights[i].radius)
			result += lightCalc(pointLights[i].position, pointLights[i].diffuse, pointLights[i].strength, pointLights[i].constant, pointLights[i].linear, pointLights[i].quadratic, fragPos, bufferNormal, bufferDif, bufferSpec, distance);	
	}

	if(result.x > bufferDif.x)
		result = bufferDif;

	fragment_color = result;

	//fragment_color = ads(lightPos, vec4(1, 1, 1, 1), fragPos, bufferNormal, bufferAmb, bufferDif, bufferSpec);

	//fragment_color = vec4(texture2D(drNormal, textureUV).rgb, 1.f);
}