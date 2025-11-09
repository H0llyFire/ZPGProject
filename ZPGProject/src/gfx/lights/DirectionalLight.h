#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
private:
	glm::vec3 _direction;
	glm::vec4 _specularColor;
public:
	DirectionalLight(glm::vec3 direction, glm::vec4 color, glm::vec4 specular);

	glm::vec3 GetDirection() const;
	glm::vec4 GetSpecularColor() const;
};
