#include "Light.h"

Light::Light()
	: Light(glm::vec3(0.f, 0.f, 0.f), glm::vec4(1.f, 1.f, 1.f, 1.f))
{
}

Light::Light(glm::vec3 pos)
	: Light(pos, glm::vec4(1.f, 1.f, 1.f, 1.f))
{
}

Light::Light(glm::vec3 pos, const glm::vec4 color)
	: _pos(pos), _color(color)
{
}

glm::vec3 Light::GetPosition() const
{
	return _pos;
}

glm::vec4 Light::GetColor() const
{
	return _color;
}
