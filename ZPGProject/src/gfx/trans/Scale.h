#pragma once
#include "TransformComponent.h"

class Scale : public TransformComponent
{
public:
	glm::vec3 ScaleVec;

	Scale(glm::vec3 scale);
	void Apply(glm::mat4& m) override;
};

