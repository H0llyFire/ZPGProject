#include "Light.h"

#include "../trans/TransformComposite.h"
#include "../ShaderProgram.h"

Light::Light(const std::shared_ptr<TransformComposite>& transforms)
	: Light(transforms, glm::vec4(1.f))
{
}

Light::Light(const std::shared_ptr<TransformComposite>& transforms, const glm::vec4 color)
	: DrawableObject(nullptr, nullptr, transforms), _color(color)
{
}

Light::Light(const std::shared_ptr<Model>& model, const std::shared_ptr<ShaderProgram>& shader,
	const std::shared_ptr<TransformComposite>& transforms, glm::vec4 color)
	: DrawableObject(model, shader, transforms), _color(color)
{
}

glm::vec3 Light::GetPosition() const
{
	return {_identity * glm::vec4(0,0,0,1)};
}

glm::vec4 Light::GetColor() const
{
	return _color;
}

bool Light::IsActive() const
{
	return _active;
}

void Light::Toggle()
{
	_active = !_active;
}

void Light::Update(float dTime)
{
	DrawableObject::Update(dTime);
	NotifyAll(LightChangedArgs(this));
}
