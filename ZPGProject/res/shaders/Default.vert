#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;
layout(location=2) in vec2 vt;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragPos;
out vec3 fragNorm;
out vec2 uv;

void main()
{
	uv = vt;
	vec4 modelPos = modelMatrix * vec4(vp, 1.0);
	fragPos = modelPos.xyz / modelPos.w;
	fragNorm = normalize(transpose(inverse(mat3(modelMatrix))) * vn);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
}	