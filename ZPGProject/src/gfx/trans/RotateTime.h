#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "Transform.h"
class RotateTime :
    public Transform
{
private:
	float _currentAngle = 0.0f;
public:
	float Angle;
	glm::vec3 Axis;

	RotateTime(float angle, glm::vec3 axis)
		: Angle(angle), Axis(axis) {}

	void Apply(glm::mat4& m, float dTime) override
	{
		_currentAngle += Angle * dTime;
		m = glm::rotate(m, _currentAngle, Axis);
	}
};

