#include "DrawableObject.h"

#include <iostream>

#include "ShaderProgram.h"
#include "Model.h"
#include "Material.h"
#include "trans/TransformComposite.h"

DrawableObject::DrawableObject(const std::shared_ptr<Model>& model, const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<TransformComposite>& transforms)
	: _shader(shader), _model(model), _material(nullptr), _trans(transforms)
{
	if (_trans != nullptr)
		_trans->Apply(_identity);
}

DrawableObject::DrawableObject(const std::shared_ptr<Model>& model, const std::shared_ptr<ShaderProgram>& shader,
	const std::shared_ptr<TransformComposite>& transforms, const std::shared_ptr<Material>& material)
	: _shader(shader), _model(model), _material(material), _trans(transforms)
{
	if (_trans != nullptr)
		_trans->Apply(_identity);
}

void DrawableObject::Update(float dTime)
{
	if (_trans != nullptr)
		_trans->Apply(_identity, dTime);
}

void DrawableObject::Draw(float dTime)
{
	if(!_shader || !_model || !_material)
	{
		std::cerr << "Tried to draw an object missing a shader / model / material.\n";
		return;
	}

	_shader->UpdateModelMatrix(_identity);
	_material->Apply(_shader);
	_shader->Bind();
	_model->Draw();
	_shader->Unbind();
}

void DrawableObject::SetMaterial(const std::shared_ptr<Material>& material)
{
	_material = material;
}

void DrawableObject::SetShader(const std::shared_ptr<ShaderProgram>& shader)
{
	_shader = shader;
}

void DrawableObject::SetModel(const std::shared_ptr<Model>& model)
{
	_model = model;
}
