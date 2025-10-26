#include "TranslateRandom.h"

TranslateRandom::TranslateRandom(float speed)
	: Speed(speed) {}

void TranslateRandom::Apply(glm::mat4& m, float dTime)
{
	//No threading used
	float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

	m = glm::translate(m, glm::vec3(x*Speed*dTime, y*Speed*dTime, z*Speed*dTime));
}
