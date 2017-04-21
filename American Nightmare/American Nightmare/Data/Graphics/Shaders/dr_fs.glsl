#version 430 core

layout (location = 0) out vec3 out_position;
layout (location = 1) out vec3 out_normal;
layout (location = 2) out vec4 out_ambient;
layout (location = 3) out vec4 out_diffuse;
layout (location = 4) out vec4 out_specular;

uniform sampler2D texture;

in vec3 position;
in vec2 textureUV;
in vec3 normal;

void main () {
	vec4 tex = texture2D(texture, vec2(textureUV.x, 1.f - textureUV.y));
	out_position = position;
	out_normal = normalize(normal);
	out_ambient = tex;
	out_diffuse = tex;
	out_specular = tex;
}