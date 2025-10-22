#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 fragPos;
out vec3 fragNorm;

void main()
{
	fragPos = modelMatrix * vec4(vp, 1.0);
	fragNorm = vn;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
}	