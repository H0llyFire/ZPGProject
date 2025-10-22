#include "TransformComposite.h"

TransformComposite::TransformComposite(const std::shared_ptr<TransformComponent>& transform)
{
	AddTransform(transform);
}

TransformComposite* TransformComposite::AddTransform(const std::shared_ptr<TransformComponent>& transform)
{
	_transforms.push_back(transform);
	return this;
}

void TransformComposite::Apply(glm::mat4& m, float dTime)
{
	for (const std::shared_ptr<TransformComponent>& t : _transforms)
		t->Apply(m, dTime);
}
