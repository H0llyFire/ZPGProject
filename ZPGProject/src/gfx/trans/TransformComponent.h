#pragma once
#include <glm/ext/matrix_float4x4.hpp>
// ReSharper disable once CppUnusedIncludeDirective
#include <glm/ext/matrix_transform.hpp>

class TransformComponent
{
public:
	virtual ~TransformComponent() = default;
	virtual void Apply(glm::mat4& m) = 0;
};

class PeriodicalTransformComponent : public TransformComponent
{
public:
	virtual void Apply(glm::mat4& m, float dTime) = 0;
	void Apply(glm::mat4& m) override {}
};
