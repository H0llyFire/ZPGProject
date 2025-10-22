#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "trans/TransformComposite.h"

class DrawableObject
{
	std::shared_ptr<ShaderProgram> _shader;
	std::shared_ptr<Model> _model;
	std::shared_ptr<TransformComposite> _trans; //Maybe change to Unique ptr later
public:
	DrawableObject(const std::shared_ptr<Model>& _model, const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<TransformComposite>& transforms);
	void Draw(float dTime) const;
};
