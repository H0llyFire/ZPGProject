#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "DrawableObject.h"
#include "../ObservableObject.h"
#include "../ObserverableArgs.h"

class ShaderProgram;
class TransformComposite;
class Light;

struct LightChangedArgs : public ObservableArgs
{
	Light* light;

	
	LightChangedArgs(Light* l)
		: light(l)
	{}
};

//While keeping the Observer pattern, maybe have light inform the scene which would then inform the shaders?
class Light : public DrawableObject, public ObservableObject
{
private:
	glm::vec4 _color;
	glm::vec4 _specularColor;
public:
	Light(const std::shared_ptr<TransformComposite>& transforms);
	Light(const std::shared_ptr<TransformComposite>& transforms, glm::vec4 color, glm::vec4 specularColor);
	Light(const std::shared_ptr<Model>& model, const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<TransformComposite>& transforms, glm::vec4 color, glm::vec4 specularColor);
	
	glm::vec3 GetPosition() const;
	glm::vec4 GetColor() const;
	glm::vec4 GetSpecularColor() const;

	void Update(float dTime) override;
};
