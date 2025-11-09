#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec4 color, glm::vec4 specular)
	: Light(nullptr, color), _direction(direction), _specularColor(specular)
{
}

glm::vec3 DirectionalLight::GetDirection() const
{
	return _direction;
}

glm::vec4 DirectionalLight::GetSpecularColor() const
{
	return _specularColor;
}
