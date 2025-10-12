#pragma once
#include <GL/glew.h>

#include <string>
#include <glm/ext/matrix_float4x4.hpp>

class Shader
{
private:
	const char* shaderPath = "res/shaders/";

	GLuint _vShader;
	GLuint _fShader;
	GLuint _program;

	void Compile(const std::string& vShaderName, const std::string& fShaderName);
	void Create();
public:
	Shader(const std::string& shaderName) : Shader(shaderName, shaderName) {}
	Shader(const std::string& vShaderName, const std::string& fShaderName);
	~Shader();
	
	void Bind();
	void Bind(glm::mat4 iMat);
	void Unbind();
};

