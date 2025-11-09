#pragma once
#include "SpotLight.h"
#include "../../Observer.h"

class FlashLight : public SpotLight, public Observer
{
public:
	FlashLight(
		const std::shared_ptr<Model>& model,
		const std::shared_ptr<ShaderProgram>& shader,
		const std::shared_ptr<TransformComposite>& transforms,
		const glm::vec4 color,
		float innerCutoff,
		float outerCutoff,
		const glm::vec4 specularColor,
		const glm::vec3 attenuationFactors);

	FlashLight(
		const std::shared_ptr<TransformComposite>& transforms,
		const glm::vec4 color,
		float innerCutoff,
		float outerCutoff,
		const glm::vec4 specularColor,
		const glm::vec3 attenuationFactors);
	
	void Notify(ObservableObject* sender, const ObservableArgs& args) override;
};
