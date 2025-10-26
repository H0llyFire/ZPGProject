#pragma once
#include <memory>
#include <vector>

#include "TransformComponent.h"

class TransformComposite : public PeriodicalTransformComponent
{
private:
	std::vector<std::shared_ptr<TransformComponent>> _transforms;
	std::vector<std::shared_ptr<PeriodicalTransformComponent>> _periodicalTransforms;
public:
	TransformComposite() = default;
	TransformComposite(const std::shared_ptr<TransformComponent>& transform);
	
	TransformComposite* AddTransform(const std::shared_ptr<TransformComponent>& transform);

	void Apply(glm::mat4& m) override;
	void Apply(glm::mat4& m, float dTime) override;
};

