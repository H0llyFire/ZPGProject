#pragma once
#include "Light.h"

class SpotLight : public Light
{
protected:
	glm::vec3 _direction;
	float _innerCutoff;
	float _outerCutoff;
	glm::vec4 _specularColor;
	glm::vec3 _attenuationFactors;
public:
	SpotLight(
		const std::shared_ptr<Model>& model,
		const std::shared_ptr<ShaderProgram>& shader,
		const std::shared_ptr<TransformComposite>& transforms,
		const glm::vec4 color,
		const glm::vec3 direction,
		float innerCutoff,
		float outerCutoff,
		const glm::vec4 specularColor,
		const glm::vec3 attenuationFactors);

	SpotLight(
		const std::shared_ptr<TransformComposite>& transforms,
		const glm::vec4 color,
		const glm::vec3 direction,
		float innerCutoff,
		float outerCutoff,
		const glm::vec4 specularColor,
		const glm::vec3 attenuationFactors);

	glm::vec3 GetDirection() const;
	float GetInnerCutoff() const;
	float GetOuterCutoff() const;
	glm::vec4 GetSpecularColor() const;
	glm::vec3 GetAttenuationFactors() const;
};
