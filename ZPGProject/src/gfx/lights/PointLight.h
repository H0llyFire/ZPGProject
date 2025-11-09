#pragma once
#include "Light.h"

class PointLight : public Light
{
private:
	glm::vec4 _specularColor;
	glm::vec3 _attenuationFactors = glm::vec3(0.f);
public:
	PointLight(
		const std::shared_ptr<TransformComposite>& transforms, 
		glm::vec4 color, 
		glm::vec4 specColor, 
		glm::vec3 attenuation);
	PointLight(
		const std::shared_ptr<Model>& model, 
		const std::shared_ptr<ShaderProgram>& shader,
		const std::shared_ptr<TransformComposite>& transforms, 
		glm::vec4 color, 
		glm::vec4 specColor, 
		glm::vec3 attenuation);

	glm::vec4 GetSpecularColor() const;
	glm::vec3 GetAttenuationFactors() const;
};
