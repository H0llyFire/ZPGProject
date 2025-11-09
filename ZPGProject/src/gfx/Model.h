#pragma once

#include <string>

#include "gfxHelpers/VertexArray.h"
#include "gfxHelpers/VertexBuffer.h"

class Model
{
private:
	VertexBuffer* _vb;
	VertexArray* _va;
	int _vertexCount;

public:
	Model(const float* points, int count);
	Model(const std::string& modelName);
	~Model();
	void Bind() const;
	void Unbind() const;
	void Draw();
};
