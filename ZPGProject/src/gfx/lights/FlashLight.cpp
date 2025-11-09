#include "FlashLight.h"

#include <iostream>

#include "../Camera.h"
#include "../../ObservableObject.h"
#include "../trans/TransformComposite.h"
#include "../trans/Translate.h"

FlashLight::FlashLight(const std::shared_ptr<Model>& model, const std::shared_ptr<ShaderProgram>& shader,
	const std::shared_ptr<TransformComposite>& transforms, const glm::vec4 color,
	float innerCutoff, float outerCutoff, const glm::vec4 specularColor, const glm::vec3 attenuationFactors)
		: SpotLight(model, shader, transforms, color, glm::vec3(0.f), innerCutoff, outerCutoff, specularColor, attenuationFactors)
{
}

FlashLight::FlashLight(const std::shared_ptr<TransformComposite>& transforms, const glm::vec4 color, 
	float innerCutoff, float outerCutoff, const glm::vec4 specularColor, const glm::vec3 attenuationFactors)
		: SpotLight(transforms, color, glm::vec3(0.f), innerCutoff, outerCutoff, specularColor, attenuationFactors)
{
}

void FlashLight::Notify(ObservableObject* sender, const ObservableArgs& args)
{
	if(auto cam = dynamic_cast<Camera*>(sender))
	{
		_direction = glm::normalize(cam->GetTarget());
	}
}
