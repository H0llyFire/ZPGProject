#include "PointLight.h"

PointLight::PointLight(const std::shared_ptr<TransformComposite>& transforms, glm::vec4 color, glm::vec4 specColor,
	glm::vec3 attenuation)
	: Light(transforms, color), _specularColor(specColor), _attenuationFactors(attenuation)
{
}

PointLight::PointLight(const std::shared_ptr<Model>& model, const std::shared_ptr<ShaderProgram>& shader,
	const std::shared_ptr<TransformComposite>& transforms, glm::vec4 color, glm::vec4 specColor, glm::vec3 attenuation)
	: Light(model, shader, transforms, color), _specularColor(specColor), _attenuationFactors(attenuation)
{
}

glm::vec4 PointLight::GetSpecularColor() const
{
	return _specularColor;
}

glm::vec3 PointLight::GetAttenuationFactors() const
{
	return _attenuationFactors;
}
