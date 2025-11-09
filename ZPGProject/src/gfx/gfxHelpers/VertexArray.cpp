#include "VertexArray.h"

#include "VertexBuffer.h"

VertexArray::VertexArray(int size)
	: _size(size)
{
	glGenVertexArrays(1, &_vao); //generate the VAO
	glBindVertexArray(_vao); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
}

void VertexArray::AddBuffer(VertexBuffer& vb)
{
	Bind();
	vb.Bind();

	if(_size>=3)
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _size * sizeof(float), (GLvoid*)0);
	}
	if(_size>=6)
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _size * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	}
	if(_size>=8)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, _size * sizeof(float), (GLvoid*)(6 * sizeof(float)));
	}
}

void VertexArray::Bind()
{
	glBindVertexArray(_vao);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}
