#include "SpotLight.h"

SpotLight::SpotLight(const std::shared_ptr<Model>& model, const std::shared_ptr<ShaderProgram>& shader,
	const std::shared_ptr<TransformComposite>& transforms, const glm::vec4 color, const glm::vec3 direction,
	float innerCutoff, float outerCutoff, const glm::vec4 specularColor, const glm::vec3 attenuationFactors)
	: Light(model, shader, transforms, color), _direction(direction), _innerCutoff(innerCutoff), _outerCutoff(outerCutoff),
	_specularColor(specularColor), _attenuationFactors(attenuationFactors)
{
}

SpotLight::SpotLight(const std::shared_ptr<TransformComposite>& transforms, const glm::vec4 color,
	const glm::vec3 direction, float innerCutoff, float outerCutoff, const glm::vec4 specularColor, const glm::vec3 attenuationFactors)
	: Light(transforms, color), _direction(direction), _innerCutoff(innerCutoff), _outerCutoff(outerCutoff), _specularColor(specularColor),
	_attenuationFactors(attenuationFactors)
{
}

glm::vec3 SpotLight::GetDirection() const
{
	return _direction;
}

float SpotLight::GetInnerCutoff() const
{
	return _innerCutoff;
}

float SpotLight::GetOuterCutoff() const
{
	return _outerCutoff;
}

glm::vec4 SpotLight::GetSpecularColor() const
{
	return _specularColor;
}

glm::vec3 SpotLight::GetAttenuationFactors() const
{
	return _attenuationFactors;
}
