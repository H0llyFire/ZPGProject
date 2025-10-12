#version 330
layout(location=0) in vec3 vp;
out float color;
void main()
{
	color = vp.z;
	gl_Position = vec4(vp.x, vp.y, 0.0, 1.0);
}