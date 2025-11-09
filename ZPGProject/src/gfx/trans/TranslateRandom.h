#pragma once
#include "TransformComponent.h"

class TranslateRandom :
    public PeriodicalTransformComponent
{
	float _duration;
	glm::vec3 _direction;
public:
	float Speed;

	TranslateRandom(float speed);
	void Apply(glm::mat4& m, float dTime) override;
};

