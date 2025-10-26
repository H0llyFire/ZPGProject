#version 330
out vec4 fragColor;


#define MAX_LIGHTS 16
struct Light
{
	vec3 position;
	vec4 color;
	vec4 specularColor;
};
uniform Light lights[MAX_LIGHTS];
uniform int lightCount;


void main() 
{
	vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);
	for (int i = 0; i < lightCount; i++) 
	{
		finalColor += lights[i].color;
	}

	fragColor = finalColor;
}