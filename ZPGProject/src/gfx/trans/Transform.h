#pragma once
#include <glm/ext/matrix_float4x4.hpp>

class Transform
{
private:
public:
	virtual void Apply(glm::mat4& m, float dTime) = 0;
};

