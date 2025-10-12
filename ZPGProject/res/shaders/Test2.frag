#version 330
in float color;
out vec4 fragColor;
void main() 
{
	fragColor = vec4(color, 0.0, color/2, 1.0);
}