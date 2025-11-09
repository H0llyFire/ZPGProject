#version 330
//Cut the file to parts later

//------------------------------------------------------------------------------
//------------------------------ STRUCTS ---------------------------------------
//------------------------------------------------------------------------------

struct PointLight
{
	bool isActive;
	vec3 position;
	vec4 color;
	vec4 specularColor;

	vec3 attenuationFactors;
};
struct SpotLight
{
	bool isActive;
	vec3 position;
	vec4 color;
	vec4 specularColor;
	
	vec3 attenuationFactors;

	vec3 direction;
	float innerCutoff;
	float outerCutoff;
};
struct DirectionalLight
{
	bool isActive;
	vec3 direction;
	vec4 color;
	vec4 specularColor;
};
struct AmbientLight
{
	bool isActive;
	vec4 color;
};

//------------------------------------------------------------------------------
//-------------------------- INPUTS / OUTPUTS ----------------------------------
//------------------------------------------------------------------------------

in vec3 fragPos;
in vec3 fragNorm;

out vec4 fragColor;

uniform vec3 cameraPos;

#define MAX_LIGHTS 32
uniform AmbientLight ambientLights[MAX_LIGHTS];
uniform int ambientLightCount;

uniform DirectionalLight directionalLights[MAX_LIGHTS];
uniform int directionalLightCount;

uniform PointLight pointLights[MAX_LIGHTS];
uniform int pointLightCount;

uniform SpotLight spotLights[MAX_LIGHTS];
uniform int spotLightCount;

uniform vec4 materialColor;
//amb, diff, spec
uniform vec3 materialReflectCoefficients;
uniform float materialShininess;

//------------------------------------------------------------------------------
//------------------------------ FUNCTIONS -------------------------------------
//------------------------------------------------------------------------------

float attenuation(float dist, vec3 attenuationFactors)
{
	float att = 1.0 / (attenuationFactors.x + attenuationFactors.y * dist + attenuationFactors.z * dist * dist);
	return clamp(att, 0.0, 1.0);
}
float intensity(vec3 normLightFragDir, vec3 normLightDir, float outerCutoff, float innerCutoff)
{
	float dotLF = dot(normLightFragDir, -normLightDir);
	float intensity = (dotLF - outerCutoff) / (innerCutoff - outerCutoff);
	intensity = clamp(intensity, 0.0, 1.0);

	return intensity;
}
float diffuse(vec3 normLightFragDir, vec3 norm)
{
	float diff = max(dot(normLightFragDir, norm), 0.0);
	return diff;
}
float blinnSpecular(vec3 normLightFragDir, vec3 normViewDir, vec3 norm)
{
	vec3 normHalfwayDir = normalize(normLightFragDir + normViewDir);
	float spec = 0.0;
	if(dot(norm, normLightFragDir) >= 0.0)
		spec = pow(max(dot(normHalfwayDir, norm), 0.0), materialShininess);
	return spec;
}
float phongSpecular(vec3 normLightFragDir, vec3 normViewDir, vec3 norm)
{
	vec3 normReflectDir = reflect(-normLightFragDir, norm);
	float spec = 0.0;
	if(dot(normLightFragDir, norm) >= 0.0)
		float spec = pow(max(dot(normViewDir, normReflectDir), 0.0), materialShininess);
	return spec;
}

//------------------------------------------------------------------------------
//------------------------------ LIGHT CALCULATIONS ----------------------------
//------------------------------------------------------------------------------

vec4 calculateDirectionalLight(DirectionalLight light, vec3 norm)
{
	if(!light.isActive)
		return vec4(0.0, 0.0, 0.0, 0.0);

	vec3 normLightFragDir = normalize(light.direction);

	vec4 diff = light.color * diffuse(normLightFragDir, norm) * materialReflectCoefficients.y;
	return diff;
}

vec4 calculateSpotLight(SpotLight light, vec3 fragPos, vec3 norm)
{
	if(!light.isActive)
		return vec4(0.0, 0.0, 0.0, 0.0);

	vec3 normLightFragDir = normalize(light.position - fragPos.xyz);

	float lightIntensity = intensity(normLightFragDir, normalize(light.direction), light.outerCutoff, light.innerCutoff);
	float dist = length(light.position - fragPos);
	float att = attenuation(dist, light.attenuationFactors);

	vec4 diff = light.color * diffuse(normLightFragDir, norm) * att * materialReflectCoefficients.y;
	return diff * lightIntensity;
}

vec4 calculatePointLight(PointLight light, vec3 fragPos, vec3 norm)
{
	if(!light.isActive)
		return vec4(0.0, 0.0, 0.0, 0.0);

	vec3 normLightFragDir = normalize(light.position - fragPos.xyz);

	float dist = length(light.position - vec3(fragPos));
	float att = attenuation(dist, light.attenuationFactors);
	
	
	vec4 diff = light.color * diffuse(normLightFragDir, norm) * att * materialReflectCoefficients.y;
	return diff;
}

vec4 calculateAmbientLight(AmbientLight light)
{
	if(!light.isActive)
		return vec4(0.0, 0.0, 0.0, 0.0);

	return light.color * materialReflectCoefficients.x;
}

//------------------------------------------------------------------------------
//------------------------------ MAIN ------------------------------------------
//------------------------------------------------------------------------------

void main(void)
{
	vec4 finalColor = vec4(0.0, 0.0, 0.0, 1.0);
	
	for(int i = 0; i < ambientLightCount; i++)
		finalColor += calculateAmbientLight(ambientLights[i]);
	for(int i = 0; i < directionalLightCount; i++)
		finalColor += calculateDirectionalLight(directionalLights[i], fragNorm);
	for(int i = 0; i < pointLightCount; i++)
		finalColor += calculatePointLight(pointLights[i], fragPos, fragNorm);
	for(int i = 0; i < spotLightCount; i++)
		finalColor += calculateSpotLight(spotLights[i], fragPos, fragNorm);
	
	fragColor = finalColor * materialColor;
}