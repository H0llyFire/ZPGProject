#pragma once
#include <memory>
#include <vector>
#include <glm/ext/matrix_float4x4.hpp>

#include "trans/Transform.h"

class Transforms
{
private:
	std::vector<std::shared_ptr<Transform>> _transforms;
public:
	Transforms() = default;
	Transforms(const std::shared_ptr<Transform>& transform);
	
	glm::mat4 GetModelMatrix() const { return GetModelMatrix(0.f); }
	glm::mat4 GetModelMatrix(float dTime) const;
	void AddTransform(const std::shared_ptr<Transform>& transform);
};
