#version 440 core

out vec4 fragment_color;
in vec2 textureUV;

uniform sampler2D texture;

void main()
{             
    //fragment_color = textureCube(texture, vec3(textureUV.x, textureUV.y, 1));
	fragment_color = texture2D(texture, textureUV);
}  
