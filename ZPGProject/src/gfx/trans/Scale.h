#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "Transform.h"
class Scale :
    public Transform
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

