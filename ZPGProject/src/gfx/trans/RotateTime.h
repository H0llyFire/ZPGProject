#pragma once
#include "TransformComponent.h"

class RotateTime : public PeriodicalTransformComponent
{
public:
	float Angle;
	glm::vec3 Axis;

	RotateTime(float angle, glm::vec3 axis);
	void Apply(glm::mat4& m, float dTime) override;
};

