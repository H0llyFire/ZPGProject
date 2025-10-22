#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "TransformComponent.h"
class Translate :
    public TransformComponent
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

