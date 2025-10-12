#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec3 color;
uniform mat4 modelMatrix;
out vec3 colorOut;
void main()
{
	colorOut = color;
	gl_Position = modelMatrix * vec4 (vp, 1.0);
}