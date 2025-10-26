#include "Rotate.h"

Rotate::Rotate(float angle, glm::vec3 axis)
	: Angle(angle), Axis(axis) {}

void Rotate::Apply(glm::mat4& m)
{
	m = glm::rotate(m, Angle, Axis);
}
