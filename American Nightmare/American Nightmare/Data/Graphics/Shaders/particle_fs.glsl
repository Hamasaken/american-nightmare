#version 400

// Input
in fData
{
    vec4 color;
}frag;  

// Output
out vec4 outputColor;

void main(void)
{
	// Setting 
	outputColor = frag.color;
}
