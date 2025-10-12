#include "Transforms.h"

Transforms::Transforms(const std::shared_ptr<Transform>& transform)
{
	AddTransform(transform);
}

glm::mat4 Transforms::GetModelMatrix(float dTime) const
{
	glm::mat4 M = glm::mat4(1.0f); // construct identity matrix

	for (const std::shared_ptr<Transform>& t : _transforms)
	{
		t->Apply(M, dTime);
	}

	return M;
}

void Transforms::AddTransform(const std::shared_ptr<Transform>& transform)
{
	_transforms.push_back(transform);
}
