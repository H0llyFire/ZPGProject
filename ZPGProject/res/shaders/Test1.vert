#version 330
layout(location=0) in vec3 vp;
out vec3 pos;
void main()
{
	pos = vp;
	gl_Position = vec4(vp, 1.0);
}