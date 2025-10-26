#pragma once
#include "TransformComponent.h"

class Translate : public TransformComponent
{
public:
	glm::vec3 TranslateVec;

	Translate(glm::vec3 translate);
	void Apply(glm::mat4& m) override;
};

