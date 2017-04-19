#version 430 core

// Uniform
uniform vec4 lightPos;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 viewPos;

uniform sampler2D drPosition;
uniform sampler2D drNormal;
uniform sampler2D drAmbient;
uniform sampler2D drDiffuse;
uniform sampler2D drSpecular;

in vec2 textureUV;

layout(location = 0) out vec4 fragment_color;

vec4 ads(vec4 lightPosition, vec4 lightColor, vec3 inFragPos, vec3 inNormal, vec4 inAmbient, vec4 inDiffuse, vec4 inSpecular) {
	vec3 normal = normalize(inNormal);

	vec3 lightDir = normalize(lightPosition.xyz - inFragPos);
	vec4 diffuseLight = inDiffuse * max(dot(normal, lightDir), 0.f);

	vec3 viewDir = normalize(viewPos.xyz - inFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float specular = pow(max(dot(viewDir, reflectDir), 0.f), 32);
	vec4 specularLight = specular * inSpecular;

	return lightColor * (inAmbient * 0.1 + diffuseLight + specularLight);
}

void main () {

	vec3 fragPos = texture2D(drPosition, textureUV).rgb;
    vec3 bufferNormal = -texture2D(drNormal, textureUV).rgb;
    vec4 bufferAmb = texture2D(drAmbient, textureUV);
	vec4 bufferDif = texture2D(drDiffuse, textureUV);
    vec4 bufferSpec = texture2D(drSpecular, textureUV);

	fragment_color = ads(lightPos, vec4(1, 1, 1, 1), fragPos, bufferNormal, bufferAmb, bufferDif, bufferSpec);

	//fragment_color = texture2D(drPosition, textureUV);
}