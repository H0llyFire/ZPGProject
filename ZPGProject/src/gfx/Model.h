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
	Model(const float* points, int count, int groupSize = 6);
	Model(const std::string& modelName, const std::string& modelExtraPath = "");
	~Model();
	void Bind() const;
	void Unbind() const;
	void Draw();
};
