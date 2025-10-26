#include "RotateTime.h"

RotateTime::RotateTime(float angle, glm::vec3 axis)
		: Angle(angle), Axis(axis) {}

void RotateTime::Apply(glm::mat4& m, float dTime)
{
	const float angle = Angle * dTime;
	m = glm::rotate(m, angle, Axis);
}
