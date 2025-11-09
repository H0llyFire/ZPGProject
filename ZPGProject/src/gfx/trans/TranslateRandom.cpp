#include "TranslateRandom.h"

TranslateRandom::TranslateRandom(float speed)
	: _duration(0.f), _direction(0.f), Speed(speed) {}

void TranslateRandom::Apply(glm::mat4& m, float dTime)
{
	if (_duration <= 0.f)
	{
		_direction.x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - .5f;
		_direction.y = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - .5f) / 10.f;
		_direction.z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - .5f;

		_duration = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) + .5f;
	}

	//No threading used

	m = glm::translate(m, glm::vec3(_direction.x*Speed*dTime, _direction.y*Speed*dTime, _direction.z*Speed*dTime));
	_duration -= dTime;
}
