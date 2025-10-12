#version 330
in vec3 colorOut;
out vec4 fragColor;
void main() 
{
	fragColor = vec4((1+colorOut.x)/2, (colorOut.y+1)/2, (1+colorOut.z)/2, 1.0);
}