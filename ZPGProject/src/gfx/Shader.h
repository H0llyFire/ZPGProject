#pragma once
#include <GL/glew.h>

#include <string>
#include <glm/ext/matrix_float4x4.hpp>

#include "../Observer.h"

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

