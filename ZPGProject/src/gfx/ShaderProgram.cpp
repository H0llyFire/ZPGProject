#include "ShaderProgram.h"

#include <fstream>
#include <iostream>

#include "Camera.h"
#include "lights/Light.h"
#include "gfxHelpers/FragmentShader.h"
#include "gfxHelpers/VertexShader.h"
#include "lights/AmbientLight.h"
#include "lights/DirectionalLight.h"
#include "lights/PointLight.h"
#include "lights/SpotLight.h"


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
		std::cerr << "Linker Failure: " << strInfoLog << "\n";
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

	Unbind();
}

ShaderProgram::ShaderProgram(const std::shared_ptr<Camera>& camera, const std::shared_ptr<VertexShader>& vertShader, const std::shared_ptr<FragmentShader>& fragShader)
	: _camera(camera)
{
	Create(vertShader, fragShader);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(_program);
}
void ShaderProgram::UpdateModelMatrix(glm::mat4 iMat) const
{
	const GLint idModelTransform = glGetUniformLocation(_program, "modelMatrix");

	Bind();
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &iMat[0][0]);
	Unbind();
}

void ShaderProgram::Bind() const
{
	glUseProgram(_program);
}

void ShaderProgram::Unbind()
{
	glUseProgram(0);
}

void ShaderProgram::UpdateLight(const Light* light, const std::string& index) const
{
	Bind();
	if(const PointLight* pl = dynamic_cast<const PointLight*>(light))
	{
		const GLint idActivity = glGetUniformLocation(_program, ("pointLights[" + index + "].isActive").c_str());
		const GLint idPosition = glGetUniformLocation(_program, ("pointLights[" + index + "].position").c_str());
		const GLint idColor = glGetUniformLocation(_program, ("pointLights[" + index + "].color").c_str());
		const GLint idSpecular = glGetUniformLocation(_program, ("pointLights[" + index + "].specularColor").c_str());
		const GLint idAttenuation = glGetUniformLocation(_program, ("pointLights[" + index + "].attenuationFactors").c_str());

		glUniform1i(idActivity, pl->IsActive() ? 1 : 0);
		glUniform3fv(idPosition, 1, &pl->GetPosition()[0]);
		glUniform4fv(idColor, 1, &pl->GetColor()[0]);
		glUniform4fv(idSpecular, 1, &pl->GetSpecularColor()[0]);
		glUniform3fv(idAttenuation, 1, &pl->GetAttenuationFactors()[0]);
	}
	else if(const SpotLight* sl = dynamic_cast<const SpotLight*>(light))
	{
		const GLint idActivity = glGetUniformLocation(_program, ("spotLights[" + index + "].isActive").c_str());
		const GLint idPosition = glGetUniformLocation(_program, ("spotLights[" + index + "].position").c_str());
		const GLint idDirection = glGetUniformLocation(_program, ("spotLights[" + index + "].direction").c_str());
		// 4h spent searching for why there was no cone even though everything looked fine.
		// .cutoff => .cutoffAngle
		//const GLint idCutoff = glGetUniformLocation(_program, ("spotLights[" + index + "].cutoff").c_str());
		const GLint idInnerCutoff = glGetUniformLocation(_program, ("spotLights[" + index + "].innerCutoff").c_str());
		const GLint idOuterCutoff = glGetUniformLocation(_program, ("spotLights[" + index + "].outerCutoff").c_str());
		const GLint idColor = glGetUniformLocation(_program, ("spotLights[" + index + "].color").c_str());
		const GLint idSpecular = glGetUniformLocation(_program, ("spotLights[" + index + "].specularColor").c_str());
		const GLint idAttenuation = glGetUniformLocation(_program, ("spotLights[" + index + "].attenuationFactors").c_str());
		
		glUniform1i(idActivity, sl->IsActive() ? 1 : 0);
		glUniform3fv(idPosition, 1, &sl->GetPosition()[0]);
		glUniform3fv(idDirection, 1, &sl->GetDirection()[0]);
		glUniform1f(idInnerCutoff, sl->GetInnerCutoff());
		glUniform1f(idOuterCutoff, sl->GetOuterCutoff());
		glUniform4fv(idColor, 1, &sl->GetColor()[0]);
		glUniform4fv(idSpecular, 1, &sl->GetSpecularColor()[0]);
		glUniform3fv(idAttenuation, 1, &sl->GetAttenuationFactors()[0]);
	}
	else if(const DirectionalLight* dl = dynamic_cast<const DirectionalLight*>(light))
	{
		const GLint idActivity = glGetUniformLocation(_program, ("directionalLights[" + index + "].isActive").c_str());
		const GLint idDirection = glGetUniformLocation(_program, ("directionalLights[" + index + "].direction").c_str());
		const GLint idColor = glGetUniformLocation(_program, ("directionalLights[" + index + "].color").c_str());
		const GLint idSpecular = glGetUniformLocation(_program, ("directionalLights[" + index + "].specularColor").c_str());
		
		glUniform1i(idActivity, dl->IsActive() ? 1 : 0);
		glUniform3fv(idDirection, 1, &dl->GetDirection()[0]);
		glUniform4fv(idColor, 1, &dl->GetColor()[0]);
		glUniform4fv(idSpecular, 1, &dl->GetSpecularColor()[0]);
	}
	else if(const AmbientLight* al = dynamic_cast<const AmbientLight*>(light))
	{
		const GLint idActivity = glGetUniformLocation(_program, ("ambientLights[" + index + "].isActive").c_str());
		const GLint idColor = glGetUniformLocation(_program, ("ambientLights[" + index + "].color").c_str());
		
		glUniform1i(idActivity, al->IsActive() ? 1 : 0);
		glUniform4fv(idColor, 1, &al->GetColor()[0]);
	}
	Unbind();

	//std::cout << "Shader " << _program << " Updated.\n";
}

void ShaderProgram::UpdatePointLightCount(int count) const
{
	const GLint idLightCount = glGetUniformLocation(_program, "pointLightCount");
	Bind();
	glUniform1i(idLightCount, count);
	Unbind();
}

void ShaderProgram::UpdateSpotLightCount(int count) const
{
	const GLint idLightCount = glGetUniformLocation(_program, "spotLightCount");
	Bind();
	glUniform1i(idLightCount, count);
	Unbind();
}

void ShaderProgram::UpdateDirectionalLightCount(int count) const
{
	const GLint idLightCount = glGetUniformLocation(_program, "directionalLightCount");
	Bind();
	glUniform1i(idLightCount, count);
	Unbind();
}

void ShaderProgram::UpdateAmbientLightCount(int count) const
{
	const GLint idLightCount = glGetUniformLocation(_program, "ambientLightCount");
	Bind();
	glUniform1i(idLightCount, count);
	Unbind();
}

void ShaderProgram::ApplyMaterial(glm::vec4 color, glm::vec3 reflectCoefficients, float shininess) const
{
	const GLint idColor = glGetUniformLocation(_program, "materialColor");
	const GLint idReflect = glGetUniformLocation(_program, "materialReflectCoefficients");
	const GLint idShininess = glGetUniformLocation(_program, "materialShininess");

	Bind();
	glUniform4fv(idColor, 1, &color[0]);
	glUniform3fv(idReflect, 1, &reflectCoefficients[0]);
	glUniform1f(idShininess, shininess);
	Unbind();
}

void ShaderProgram::Notify(ObservableObject* sender, const ObservableArgs& args)
{
	if(Camera* camera = dynamic_cast<Camera*>(sender))
	{
		UpdateCamera();
	}
}


