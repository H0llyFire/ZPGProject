#pragma once
#include <glm/ext/matrix_float4x4.hpp>

class TransformComponent
{
private:
public:
	virtual ~TransformComponent() = default;
	virtual void Apply(glm::mat4& m, float dTime) = 0;
};

