#include "DrawableObject.h"

DrawableObject::DrawableObject(const std::shared_ptr<Model>& _model, const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<TransformComposite>& transforms)
	: _shader(shader), _model(_model), _trans(transforms)
{

}

void DrawableObject::Draw(float dTime) const
{
	glm::mat4 identity(1.0f);
	if (_trans != nullptr)
		_trans->Apply(identity, dTime);
	_shader->Bind(identity);
	_model->Draw();
}
