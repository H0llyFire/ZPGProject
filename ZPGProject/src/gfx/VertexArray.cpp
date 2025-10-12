#include "VertexArray.h"

#include <GL/glew.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_vao); //generate the VAO
	glBindVertexArray(_vao); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
}

void VertexArray::AddBuffer(VertexBuffer& vb)
{
	Bind();
	vb.Bind();
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//index, pocet, typ, normalized, velikost jednoho vrcholu, pocatek
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}

void VertexArray::Bind()
{
	glBindVertexArray(_vao);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}
