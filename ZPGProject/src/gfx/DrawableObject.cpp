#include "DrawableObject.h"

#include "ShaderProgram.h"
#include "Model.h"
#include "trans/TransformComposite.h"

DrawableObject::DrawableObject(const std::shared_ptr<Model>& model, const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<TransformComposite>& transforms)
	: _shader(shader), _model(model), _trans(transforms)
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
	if(_shader == nullptr || _model == nullptr)
		return;
	_shader->Bind(_identity);
	_model->Draw();
}
