#pragma once
#include "VertexBuffer.h"

class VertexArray
{
	GLuint _vao = 0;
public:
	VertexArray();
	void AddBuffer(VertexBuffer& vb);
	void Bind();
	void Unbind();
};
