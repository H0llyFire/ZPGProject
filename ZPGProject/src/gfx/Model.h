#pragma once
#include "gfxHelpers/VertexArray.h"
#include "gfxHelpers/VertexBuffer.h"

class Model
{
private:
	VertexBuffer _vb;
	VertexArray _va;
	int _vertexCount;

public:
	Model(const float* points, int count);
	void Bind();
	void Draw();
};
