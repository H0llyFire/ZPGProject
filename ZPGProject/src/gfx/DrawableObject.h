#pragma once
#include <memory>
#include <glm/ext/matrix_float4x4.hpp>

class ShaderProgram;
class Model;
class TransformComposite;

class DrawableObject
{
protected:
	std::shared_ptr<ShaderProgram> _shader;
	std::shared_ptr<Model> _model;
	std::shared_ptr<TransformComposite> _trans; //Maybe change to Unique ptr later

	glm::mat4 _identity = glm::mat4(1.0f);
public:
	DrawableObject(const std::shared_ptr<Model>& model, const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<TransformComposite>& transforms);
	virtual ~DrawableObject() = default;
	virtual void Update(float dTime);
	virtual void Draw(float dTime);

	std::shared_ptr<ShaderProgram> GetShader() const
	{
		return _shader;
	}
};
