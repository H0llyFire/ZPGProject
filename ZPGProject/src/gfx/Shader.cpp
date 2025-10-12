#include "Shader.h"
#include "Camera.h"

#include <fstream>
#include <iostream>
#include <sstream>

void Shader::Compile(const std::string& vShaderName, const std::string& fShaderName)
{
    std::ifstream vShaderFile, fShaderFile;
    std::string vShaderStr, fShaderStr;
    try 
    {
        std::stringstream vShaderStream, fShaderStream;
        
        vShaderFile.open(shaderPath + vShaderName + ".vert");
        vShaderStream << vShaderFile.rdbuf();
        vShaderFile.close();

        fShaderFile.open(shaderPath + fShaderName + ".frag");
        fShaderStream << fShaderFile.rdbuf();
        fShaderFile.close();

        vShaderStr   = vShaderStream.str();
        fShaderStr = fShaderStream.str();
    }
    catch(std::ifstream::failure &e)
    {
        std::cout << "Shader Reading Error\n";
    }

    const char* fShader = fShaderStr.c_str();
    const char* vShader = vShaderStr.c_str();

	_vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vShader, 1, &vShader, nullptr);
	glCompileShader(_vShader);

	_fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fShader, 1, &fShader, nullptr);
	glCompileShader(_fShader);
}

void Shader::Create()
{
	_program = glCreateProgram();
	glAttachShader(_program, _fShader);
	glAttachShader(_program, _vShader);
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

Shader::Shader(Camera* camera, const std::string& vShaderName, const std::string& fShaderName)
	: _camera(camera)
{
	Compile(vShaderName, fShaderName);
	Create();
	_camera->AddShader(this);
}

Shader::~Shader()
{
	_camera->RemoveShader(this);
	glDeleteProgram(_program);
	glDeleteShader(_fShader);
	glDeleteShader(_vShader);
}

void Shader::Bind()
{
	glUseProgram(_program);
}
void Shader::Bind(glm::mat4 iMat)
{
	glUseProgram(_program);
	const GLint idModelTransform = glGetUniformLocation(_program, "modelMatrix");
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &iMat[0][0]);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::UpdateCameraMatrices()
{
	Bind();
	const GLint idViewMatrix = glGetUniformLocation(_program, "viewMatrix");
	glUniformMatrix4fv(idViewMatrix, 1, GL_FALSE, &_camera->GetCamera()[0][0]);
	const GLint idProjectionMatrix = glGetUniformLocation(_program, "projectionMatrix");
	glUniformMatrix4fv(idProjectionMatrix, 1, GL_FALSE, &_camera->GetProjection()[0][0]);
}

