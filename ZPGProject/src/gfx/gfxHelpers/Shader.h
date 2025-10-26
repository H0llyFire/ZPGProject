#pragma once
#include <GL/glew.h>

#include <string>

class Camera;

class Shader
{
protected:
	const char* _shaderPath = "res/shaders/";
	GLuint _shader;

	Shader() = default;
public:
	~Shader();
	void AttachToProgram(GLuint program) const;
};

