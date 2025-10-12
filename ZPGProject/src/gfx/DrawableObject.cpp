#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* _model, Shader* shader, Transforms* transforms)
	: _shader(shader), _model(_model), _trans(transforms)
{

}

void DrawableObject::Draw(float dTime) const
{
	_shader->Bind(_trans->GetModelMatrix(dTime));
	_model->Draw();
}
