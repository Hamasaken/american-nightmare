#version 430

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

// Input
in vec2 textureUV;
in vec3 position;
in vec3 normalw;

// Uniform
uniform int nrOfPointLights;
uniform PointLight pointLights[100];

uniform int nrOfDirectionalLights;
uniform DirectionalLight directionalLights[10];

uniform vec4 viewPos;

uniform sampler2D texture;
uniform sampler2D normal;
uniform sampler2D shadowmap;

uniform mat4 lightSpaceMatrix;
uniform bool useShadow;
uniform bool isRight;

// Output
layout(location = 0) out vec4 fragment_color;

float calculateShadow(vec3 lightSpacePos)
{
	float bias = 0.005f;
  
	float currentDepth = lightSpacePos.z;
	//float closestDepth = texture(shadowmap, lightSpacePos.xy).r; 
	//float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

	// PCF
	float shadow = 0.f;
	vec2 texelSize = 1.0 / textureSize(shadowmap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture2D(shadowmap, lightSpacePos.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;

	if(lightSpacePos.z > 1.0)
		shadow = 0.0;

	return shadow;
}

vec4 pointLightCalc(vec4 lightPosition, vec4 lightDiffuse, float strength, float lightConstant, float lightLinear, float lightQuadratic, vec3 inFragPos, vec3 inNormal, vec4 inTexDiffuse, float inDistance, float shadow)
{
	vec3 normal = normalize(inNormal);

	vec3 lightDir = normalize(lightPosition.xyz - inFragPos);
	vec4 diffuseLight = inTexDiffuse * max(dot(normal, lightDir), 0.f);

	vec3 viewDir = normalize(viewPos.xyz - inFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float specular = pow(max(dot(viewDir, reflectDir), 0.f), 32);
	vec4 specularLight = specular * vec4(0, 0, 0, 1);

	float attenuation = 1.0 / (1.0 + lightLinear * inDistance + lightQuadratic * inDistance * inDistance);

	return strength * (1.f - shadow) * (diffuseLight * lightDiffuse * attenuation + specularLight * attenuation);
}

vec4 directionalLightCalc(vec4 lightDirection, vec4 lightDiffuse, vec4 lightSpecular, float strength, vec3 inFragPos, vec3 inNormal, vec4 inDiffuse, float shadow)
{
	vec3 normal = normalize(inNormal);
	vec3 lightDir = normalize(-lightDirection.xyz);

	vec4 diffuseLight = inDiffuse * max(dot(normal, lightDir), 0.f);

	vec3 viewDir = normalize(viewPos.xyz - inFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float specular = pow(max(dot(viewDir, reflectDir), 0.f), 32);
	vec4 specularLight = specular * vec4(0, 0, 0, 1) * lightSpecular;

	return strength * (1.f - shadow) * (diffuseLight * lightDiffuse + specularLight * 0.2);
}

void main(void)
{
	vec4 bufferColor = texture2D(texture, vec2(textureUV.x, 1.f - textureUV.y));
	vec3 bufferNormal = texture2D(normal, vec2(textureUV.x, 1.f - textureUV.y)).rgb;
	bufferNormal = normalize(bufferNormal * 2.0 - 1.0);

	float shadow = 0;

	if(useShadow)
	{
		vec4 lightSpacePos = lightSpaceMatrix * vec4(position, 1.f);
		vec3 finalLightSpacePos = lightSpacePos.xyz / lightSpacePos.w;
		finalLightSpacePos = finalLightSpacePos * 0.5f + 0.5f;

		shadow = calculateShadow(finalLightSpacePos);
	}

	if (!isRight)
		bufferNormal.x = bufferNormal.x * -1.f;

	vec4 result = vec4(0);

	result += bufferColor * 0.1f;

	for(int i = 0; i < nrOfPointLights; i++)
	{
		float distance = length(pointLights[i].position.xyz - position);

		if(distance < pointLights[i].radius)
			result += pointLightCalc(pointLights[i].position, pointLights[i].diffuse, pointLights[i].strength, pointLights[i].constant, pointLights[i].linear, pointLights[i].quadratic, position, bufferNormal, bufferColor, distance, shadow);	
	}
	
	for(int i = 0; i < nrOfDirectionalLights; i++)
	{
		result += directionalLightCalc(directionalLights[i].direction, directionalLights[i].diffuse, directionalLights[i].specular, directionalLights[i].strength, position, bufferNormal, bufferColor, shadow);
	}
	

	if(result.x > bufferColor.x || result.y > bufferColor.y || result.z > bufferColor.z)
		result = bufferColor;


	fragment_color = vec4(result.rgb, bufferColor.a);

	//fragment_color = vec4(bufferNormal, bufferColor.a);
	//fragment_color = vec4(normalw, bufferColor.a);
}