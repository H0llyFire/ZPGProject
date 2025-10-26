#include "Shader.h"

Shader::~Shader()
{
	glDeleteShader(_shader);
}

void Shader::AttachToProgram(GLuint program) const
{
	glAttachShader(program, _shader);
}
