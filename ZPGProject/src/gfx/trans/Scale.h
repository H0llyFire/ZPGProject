#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "TransformComponent.h"
class Scale :
    public TransformComponent
{
private:
public:
	glm::vec3 ScaleVec;

	Scale(glm::vec3 scale)
		: ScaleVec(scale) {}

	void Apply(glm::mat4& m, float dTime) override
	{
		m = glm::scale(m, ScaleVec);
	}
};

