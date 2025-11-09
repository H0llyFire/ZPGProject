#pragma once
#include <GL/glew.h>

class VertexBuffer;

class VertexArray
{
	GLuint _vao = 0;
	int _size;
public:
	VertexArray(int size);
	void AddBuffer(VertexBuffer& vb);
	void Bind();
	void Unbind();
};
