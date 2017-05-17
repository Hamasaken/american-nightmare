#version 430 core

in vec4 fragPos;

uniform vec4 lightPosisiton;
uniform float lightFarPlane;

void main()
{
    // get distance between fragment and light source
    float lightDistance = length(fragPos.xyz - lightPosisiton.xyz);
    
    // map to [0;1] range by dividing by lightFarPlane
    lightDistance = lightDistance / lightFarPlane;
    
    // Write this as modified depth
    gl_FragDepth = lightDistance;
}  