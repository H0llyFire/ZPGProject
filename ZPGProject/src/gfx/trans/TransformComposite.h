#pragma once
#include <memory>
#include <vector>
#include <glm/ext/matrix_float4x4.hpp>

#include "TransformComponent.h"

class TransformComposite : public TransformComponent
{
private:
	std::vector<std::shared_ptr<TransformComponent>> _transforms;
public:
	TransformComposite() = default;
	TransformComposite(const std::shared_ptr<TransformComponent>& transform);
	
	TransformComposite* AddTransform(const std::shared_ptr<TransformComponent>& transform);
	
	void Apply(glm::mat4& m, float dTime) override;
};
