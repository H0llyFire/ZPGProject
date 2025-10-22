#version 330
in vec4 fragPos;
in vec3 fragNorm;

out vec4 fragColor;

uniform vec3 lightPos;
uniform vec3 cameraPos;

void main(void)
{
	vec3 normLightDir = normalize(lightPos - fragPos.xyz);
	vec3 normReflectDir = reflect(-normLightDir, fragNorm);
	vec3 normViewDir = normalize(cameraPos - fragPos.xyz);

	float diff = max(dot(normLightDir, fragNorm), 0.0);
	float spec = pow(max(dot(normViewDir, normReflectDir), 0.0), 32.0);

	vec4 ambient = vec4 (0.04 ,0.04 ,0.04 ,1.0);
	vec4 objectColor = vec4 (0.185 ,0.947 ,0.512 ,1.0);
	vec4 specColor = vec4(1.0, 1.0, 1.0, 1.0);

	fragColor = ambient + (diff * objectColor) + (spec * specColor);
}