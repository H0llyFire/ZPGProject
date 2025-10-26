#pragma once
#include "TransformComponent.h"

class Rotate :
    public TransformComponent
{
public:
	float Angle;
	glm::vec3 Axis;

	Rotate(float angle, glm::vec3 axis);
	void Apply(glm::mat4& m) override;
};

