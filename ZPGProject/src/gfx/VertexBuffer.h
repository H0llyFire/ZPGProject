#pragma once

#include <GL/glew.h>

class VertexBuffer
{
	GLuint _vbo = 0;
public:
	VertexBuffer(const float* points, size_t count);
	void Bind();
	void Unbind();
};
