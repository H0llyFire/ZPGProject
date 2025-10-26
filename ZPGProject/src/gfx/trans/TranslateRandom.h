#pragma once
#include "TransformComponent.h"

class TranslateRandom :
    public PeriodicalTransformComponent
{
public:
	float Speed;

	TranslateRandom(float speed);
	void Apply(glm::mat4& m, float dTime) override;
};

