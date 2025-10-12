#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "Transform.h"
class Rotate :
    public Transform
{
private:
public:
	float Angle;
	glm::vec3 Axis;

	Rotate(float angle, glm::vec3 axis)
		: Angle(angle), Axis(axis) {}

	void Apply(glm::mat4& m, float dTime) override
	{
		m = glm::rotate(m, Angle, Axis);
	}
};

