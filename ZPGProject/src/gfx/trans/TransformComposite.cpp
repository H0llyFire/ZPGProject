#include "TransformComposite.h"

TransformComposite::TransformComposite(const std::shared_ptr<TransformComponent>& transform)
{
	AddTransform(transform);
}

TransformComposite* TransformComposite::AddTransform(const std::shared_ptr<TransformComponent>& transform)
{
	if(std::dynamic_pointer_cast<TransformComposite>(transform))
		_transforms.push_back(transform);

	if(const std::shared_ptr<PeriodicalTransformComponent> trans = std::dynamic_pointer_cast<PeriodicalTransformComponent>(transform))
		_periodicalTransforms.push_back(trans);
	else
		_transforms.push_back(transform);

	return this;
}

void TransformComposite::Apply(glm::mat4& m)
{
	for (const std::shared_ptr<TransformComponent>& t : _transforms)
		t->Apply(m);
}

void TransformComposite::Apply(glm::mat4& m, float dTime)
{
	for (const std::shared_ptr<PeriodicalTransformComponent>& t : _periodicalTransforms)
		t->Apply(m, dTime);
}

void TransformComposite::Clear()
{
	_transforms.clear();
	_periodicalTransforms.clear();
}
