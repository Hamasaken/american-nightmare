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

struct DirectionalLight
{
	vec4 direction;

	vec4 diffuse;
	vec4 specular;

	float strength;
};

struct DirectionalShadowMaps
{
	sampler2D shadowmap;
	mat4 lightSpaceMatrix;
	vec4 lightDirection;
};

// Uniform
// Lights
uniform int nrOfPointLights;
uniform PointLight pointLights[100];

uniform int nrOfDirectionalLights;
uniform DirectionalLight directionalLights[10];

// Shadows
uniform int nrOfDirectionalShadowMaps;
uniform DirectionalShadowMaps directionalShadowMaps[5];

//uniform int nrOfPointShadowMaps;
//uniform sampler2D pointShadowMaps[5];

uniform vec4 viewPos;

uniform sampler2D drPosition;
uniform sampler2D drNormal;
uniform sampler2D drAmbient;
uniform sampler2D drDiffuse;
uniform sampler2D drSpecular;

uniform bool useShadow;

// Input
in vec2 textureUV;

// Output
layout(location = 0) out vec4 fragment_color;

float calculateShadow(vec3 lightSpacePos, vec3 normal, int shadowMapIndex)
{
	float bias = max(0.01 * (1.0 - dot(normal, directionalShadowMaps[shadowMapIndex].lightDirection.xyz)), 0.005);
  
	float currentDepth = lightSpacePos.z;
	//float closestDepth = texture(directionalShadowMaps[shadowMapIndex].shadowmap, lightSpacePos.xy).r; 
	//float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

	// PCF
	float shadow = 0.f;
	vec2 texelSize = 1.0 / textureSize(directionalShadowMaps[shadowMapIndex].shadowmap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture2D(directionalShadowMaps[shadowMapIndex].shadowmap, lightSpacePos.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;

	if(lightSpacePos.z > 1.0)
		shadow = 0.f;

	return shadow;
}

vec4 pointLightCalc(vec4 lightPosition, vec4 lightDiffuse, vec4 lightSpecular, float strength, float lightConstant, float lightLinear, float lightQuadratic, vec3 inFragPos, vec3 inNormal, vec4 inDiffuse, vec4 inSpecular, float inDistance, float shadow) 
{
	vec3 normal = normalize(inNormal);

	vec3 lightDir = normalize(lightPosition.xyz - inFragPos);
	vec4 diffuseLight = inDiffuse * max(dot(normal, lightDir), 0.f);

	vec3 viewDir = normalize(viewPos.xyz - inFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float specular = pow(max(dot(viewDir, reflectDir), 0.f), 32);
	vec4 specularLight = specular * inSpecular * lightSpecular;

	float attenuation = 1.0 / (1.0 + lightLinear * inDistance + lightQuadratic * inDistance * inDistance);

	return strength * (1.f - shadow) * (diffuseLight * lightDiffuse * attenuation + specularLight * 0.2 * attenuation);
}

vec4 directionalLightCalc(vec4 lightDirection, vec4 lightDiffuse, vec4 lightSpecular, float strength, vec3 inFragPos, vec3 inNormal, vec4 inDiffuse, vec4 inSpecular, float shadow)
{
	vec3 normal = normalize(inNormal);
	vec3 lightDir = normalize(-lightDirection.xyz);

	vec4 diffuseLight = inDiffuse * max(dot(normal, lightDir), 0.f);

	vec3 viewDir = normalize(viewPos.xyz - inFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float specular = pow(max(dot(viewDir, reflectDir), 0.f), 32);
	vec4 specularLight = specular * inSpecular * lightSpecular;

	return strength * (1.f - shadow) * (diffuseLight * lightDiffuse + specularLight * 0.2);
}

void main () {

	vec3 fragPos = texture2D(drPosition, textureUV).rgb;
    vec3 bufferNormal = texture2D(drNormal, textureUV).rgb;
    vec4 bufferAmb = texture2D(drAmbient, textureUV);
	vec4 bufferDif = texture2D(drDiffuse, textureUV);
    vec4 bufferSpec = texture2D(drSpecular, textureUV);

	vec4 result = vec4(0);

	result += bufferAmb * 0.3f;

	float shadow = 0;
	
	if(useShadow)
	{
		for(int i = 0; i < 3; i++)
		{
			vec4 lightSpacePos = directionalShadowMaps[i].lightSpaceMatrix * vec4(fragPos, 1.f);
			vec3 finalLightSpacePos = lightSpacePos.xyz / lightSpacePos.w;
			finalLightSpacePos = finalLightSpacePos * 0.5f + 0.5f;

			shadow += calculateShadow(finalLightSpacePos, bufferNormal, i);
		}

		shadow /= nrOfDirectionalShadowMaps;

		if(shadow > 1.f)
			shadow = 1.f;
	}

	for(int i = 0; i < nrOfPointLights; i++)
	{
		float distance = length(pointLights[i].position.xyz - fragPos);

		if(distance < pointLights[i].radius)
			result += pointLightCalc(pointLights[i].position, pointLights[i].diffuse, pointLights[i].specular, pointLights[i].strength, pointLights[i].constant, pointLights[i].linear, pointLights[i].quadratic, fragPos, bufferNormal, bufferDif, bufferSpec, distance, shadow);	
	}

	for(int i = 0; i < nrOfDirectionalLights; i++)
	{
		result += directionalLightCalc(directionalLights[i].direction, directionalLights[i].diffuse, directionalLights[i].specular, directionalLights[i].strength, fragPos, bufferNormal, bufferDif, bufferSpec, shadow);
	}

	

	if(result.x > bufferDif.x || result.y > bufferDif.y || result.z > bufferDif.z)
		result = bufferDif;

	fragment_color = result;
}