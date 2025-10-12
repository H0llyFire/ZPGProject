#pragma once
#include <GL/glew.h>

#include <string>
#include <glm/ext/matrix_float4x4.hpp>

class Camera;

class Shader
{
private:
	const char* shaderPath = "res/shaders/";
	Camera* _camera;

	GLuint _vShader;
	GLuint _fShader;
	GLuint _program;

	void Compile(const std::string& vShaderName, const std::string& fShaderName);
	void Create();
public:
	Shader(Camera* camera, const std::string& shaderName) : Shader(camera, shaderName, shaderName) {}
	Shader(Camera* camera, const std::string& vShaderName, const std::string& fShaderName);
	~Shader();
	
	void Bind();
	void Bind(glm::mat4 iMat);
	void Unbind();

	void UpdateCameraMatrices();
};

