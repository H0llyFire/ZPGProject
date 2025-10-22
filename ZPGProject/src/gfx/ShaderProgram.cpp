#include "ShaderProgram.h"
#include "Shader.h"
#include "Camera.h"

#include <fstream>
#include <iostream>
#include <sstream>


void ShaderProgram::Create(const std::shared_ptr<VertexShader>& vertShader, const std::shared_ptr<FragmentShader>& fragShader)
{
	_program = glCreateProgram();

	vertShader->AttachToProgram(_program);
	fragShader->AttachToProgram(_program);

	glLinkProgram(_program);

	GLint status;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
	    GLint infoLogLength;
	    glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogLength);
	    GLchar *strInfoLog = new GLchar[infoLogLength + 1];
	    glGetProgramInfoLog(_program, infoLogLength, NULL, strInfoLog);
	    fprintf(stderr, "Linker failure: %s\n", strInfoLog);
	    delete[] strInfoLog;
	}
}

void ShaderProgram::UpdateCamera() const
{
	const GLint idViewMatrix = glGetUniformLocation(_program, "viewMatrix");
	const GLint idProjectionMatrix = glGetUniformLocation(_program, "projectionMatrix");
	const GLint idCameraPos = glGetUniformLocation(_program, "cameraPos");
	
	Bind();
	glUniformMatrix4fv(idViewMatrix, 1, GL_FALSE, &_camera->GetCamera()[0][0]);
	glUniformMatrix4fv(idProjectionMatrix, 1, GL_FALSE, &_camera->GetProjection()[0][0]);
	glUniform3fv(idCameraPos, 1, &_camera->GetPosition()[0]);
}

void ShaderProgram::UpdateLight() const
{
	const GLint idLightPos = glGetUniformLocation(_program, "lightPos");
	const GLint idLightColor = glGetUniformLocation(_program, "lightColor");
	Bind();

	if(_light == nullptr)
	{
		glm::vec3 lightPos{ 0.f, 0.f, 0.f };
		glm::vec4 ligtColor{0.f, 0.f, 0.f, 0.f};

		glUniform3fv(idLightPos, 1, &lightPos[0]);
		glUniform4fv(idLightColor, 1, &ligtColor[0]);
		return;
	}

	glUniform3fv(idLightPos, 1, &_light->GetPosition()[0]);
	glUniform4fv(idLightColor, 1, &_light->GetColor()[0]);
}

ShaderProgram::ShaderProgram(const std::shared_ptr<Camera>& camera, const std::shared_ptr<VertexShader>& vertShader, const std::shared_ptr<FragmentShader>& fragShader)
	: _camera(camera), _light(nullptr)
{
	Create(vertShader, fragShader);
	UpdateLight();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(_program);
}

void ShaderProgram::Bind() const
{
	glUseProgram(_program);
}
void ShaderProgram::Bind(glm::mat4 iMat) const
{
	glUseProgram(_program);
	const GLint idModelTransform = glGetUniformLocation(_program, "modelMatrix");
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &iMat[0][0]);
}

void ShaderProgram::Unbind()
{
	glUseProgram(0);
}

void ShaderProgram::ChangeLight(const std::shared_ptr<Light>& light)
{
	_light = light;
	UpdateLight();
}

void ShaderProgram::Notify()
{
	UpdateCamera();
	UpdateLight();
}


