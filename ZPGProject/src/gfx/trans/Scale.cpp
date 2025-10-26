#include "Scale.h"

Scale::Scale(glm::vec3 scale)
		: ScaleVec(scale) {}

void Scale::Apply(glm::mat4& m)
{
	m = glm::scale(m, ScaleVec);
}
