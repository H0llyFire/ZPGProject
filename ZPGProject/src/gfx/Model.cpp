#include "Model.h"

Model::Model(const float* points, int count)
	: _vb(VertexBuffer(points, count)), _va(VertexArray()), _vertexCount(count / 6)
{
	_va.AddBuffer(_vb);
}

void Model::Draw()
{
	Bind();
	glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
}

void Model::Bind()
{
	_va.Bind();
}