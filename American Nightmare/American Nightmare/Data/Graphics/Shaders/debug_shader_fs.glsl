#version 430 core

out vec3 fragment_color;
in vec2 textureUV;

uniform sampler2D texture;

void main()
{             
    fragment_color = texture2D(texture, textureUV).rgb;
	//fragment_color = vec4(0, 1, 0, 1);
}  
