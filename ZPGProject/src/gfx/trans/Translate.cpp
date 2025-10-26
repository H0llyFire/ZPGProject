#include "Translate.h"

Translate::Translate(glm::vec3 translate)
	: TranslateVec(translate) {}

void Translate::Apply(glm::mat4& m)
{
	m = glm::translate(m, TranslateVec);
}
