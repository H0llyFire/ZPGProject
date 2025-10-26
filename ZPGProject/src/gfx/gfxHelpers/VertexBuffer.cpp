#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const float* points, size_t count)
{
	//vertex buffer object (VBO)
	glGenBuffers(1, &_vbo); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*count, points, GL_STATIC_DRAW);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
