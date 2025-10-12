#pragma once
#include "Model.h"
#include "Shader.h"
#include "Transforms.h"

class DrawableObject
{
	Shader* _shader;
	Model* _model;
	Transforms* _trans;
public:
	DrawableObject(Model* _model, Shader* shader, Transforms* transforms);
	void Draw(float dTime) const;
};
