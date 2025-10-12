#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "Transform.h"
class Translate :
    public Transform
{
private:
public:
	glm::vec3 TranslateVec;
	Translate(glm::vec3 translate)
		: TranslateVec(translate) {}

	void Apply(glm::mat4& m, float dTime) override
	{
		m = glm::translate(m, TranslateVec);
	}
};

