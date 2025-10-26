#version 330
in vec4 fragPos;
in vec3 fragNorm;

out vec4 fragColor;

#define MAX_LIGHTS 16
struct Light
{
	vec3 position;
	vec4 color;
	vec4 specularColor;

	vec3 attenuationFactors;
};

uniform vec3 cameraPos;
uniform vec4 ambientColor;

uniform Light lights[MAX_LIGHTS];
uniform int lightCount;


float attenuation(float dist, float c, float l, float q)
{
	// d = distance from the light to the fragment
	// c = constant attenuation factor
	// l = linear attenuation factor
	// q = quadratic attenuation factor

	float att = 1.0 / (c + l * dist + q * dist * dist);
	return clamp(att, 0.0, 1.0);
}


void main(void)
{
	vec4 finalColor = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 finalSpecColor = vec4(0.0, 0.0, 0.0, 1.0);

	vec4 objectColor = vec4(0.2, 0.9, 0.4, 1.0);


	for(int i = 0; i < lightCount; i++)
	{
		vec3 normLightDir = normalize(lights[i].position - fragPos.xyz);
		vec3 normViewDir = normalize(cameraPos - fragPos.xyz);
		vec3 normHalfwayDir = normalize(normLightDir + normViewDir);
		
		float dist = length(lights[i].position - vec3(fragPos));
		float att = attenuation(dist, 1.0, 0.4, 0.6);

		float diff = att * max(dot(normLightDir, fragNorm), 0.0);
		float spec = att * pow(max(dot(normHalfwayDir, fragNorm), 0.0), 40.0);
		if(dot(fragNorm, normLightDir) < 0.0)
		{
			spec = 0.0;
		}

		finalColor += lights[i].color * objectColor * diff;
		finalSpecColor += lights[i].specularColor * spec;
	}

	
	vec4 ambient = objectColor * 0.05;

	fragColor = ambient + finalColor + finalSpecColor;
}