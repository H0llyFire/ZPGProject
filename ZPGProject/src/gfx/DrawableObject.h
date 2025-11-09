#pragma once
#include <memory>
#include <glm/ext/matrix_float4x4.hpp>

#include "../ResourceManager.h"

class TextureUnitManager;
class Texture;
class Material;
class ShaderProgram;
class Model;
class TransformComposite;

class DrawableObject
{
protected:
	std::shared_ptr<ShaderProgram> _shader;
	std::shared_ptr<Model> _model;
	std::shared_ptr<Material> _material;
	std::shared_ptr<Texture> _texture;
	//TODO: Change to unique ptr
	std::shared_ptr<TransformComposite> _trans;

	glm::mat4 _identity = glm::mat4(1.0f);
public:
	DrawableObject(
		const std::shared_ptr<TransformComposite>& transforms = nullptr,
		const std::shared_ptr<Model>& model = nullptr, 
		const std::shared_ptr<ShaderProgram>& shader = nullptr,
		const std::shared_ptr<Material>& material = nullptr,
		const std::shared_ptr<Texture>& texture = nullptr);
	DrawableObject(const std::shared_ptr<Model>& model, const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<TransformComposite>& transforms);
	DrawableObject(const std::shared_ptr<Model>& model, const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<TransformComposite>& transforms, const std::shared_ptr<Material>& material);
	virtual ~DrawableObject() = default;
	virtual void Update(float dTime);
	virtual void Draw(float dTime, std::shared_ptr<TextureUnitManager> tuMngr);

	void SetMaterial(const std::shared_ptr<Material>& material);
	void SetShader(const std::shared_ptr<ShaderProgram>& shader);
	void SetModel(const std::shared_ptr<Model>& model);
	void SetTexture(const std::shared_ptr<Texture>& texture);

	std::shared_ptr<ShaderProgram> GetShader() const;
};
