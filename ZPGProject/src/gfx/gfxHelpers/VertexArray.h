#pragma once
#include <GL/glew.h>

class VertexBuffer;

class VertexArray
{
	GLuint _vao = 0;
public:
	VertexArray();
	void AddBuffer(VertexBuffer& vb);
	void Bind();
	void Unbind();
};
