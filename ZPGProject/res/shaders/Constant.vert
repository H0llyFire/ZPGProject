#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec3 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 colorOut;
void main()
{
	colorOut = vec3(0.1, 0.9, 0.65);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);
}