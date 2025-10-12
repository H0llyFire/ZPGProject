#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"

void Camera::CalcViewMat()
{
	_viewMat = glm::lookAt(_eye, _eye+_target, _up);
	NotifyShaders();
}

void Camera::CalcProjMat()
{
	_projMat = glm::perspective(glm::radians(60.f), _ratioWidth / _ratioHeight, 0.1f, 100.0f);
	NotifyShaders();
}

Camera::Camera(float ratioWidth, float ratioHeight)
	: _eye(0.f, 0.f, 0.f), _target(0.f, 0.f, 0.f), _up(0.f, 1.f, 0.f), _ratioWidth(ratioWidth), _ratioHeight(ratioHeight)
{
	CalcViewMat();
	CalcProjMat();
}

Camera::Camera(float ratioWidth, float ratioHeight, Shader* shader)
	: _eye(0.f, 0.f, 0.f), _target(0.f, 0.f, 0.f), _up(0.f, 1.f, 0.f), _ratioWidth(ratioWidth), _ratioHeight(ratioHeight)
{
	AddShader(shader);
	CalcViewMat();
	CalcProjMat();
}

glm::mat4 Camera::GetCamera()
{
	return _viewMat;
}

glm::mat4 Camera::GetProjection()
{
	return _projMat;
}

void Camera::CalcTarget(float yaw, float pitch)
{
	_yaw += yaw;
	_pitch += pitch;
	if(_pitch > glm::radians(179.9f))
		_pitch = glm::radians(179.9f);
	else if(_pitch < glm::radians(0.1f))
		_pitch = glm::radians(0.1f);
	/*
	_target.x = cos(_pitch) * cos(_yaw);
	_target.y = sin(_pitch);
	_target.z = cos(_pitch) * sin(_yaw);
	*/

	_target.x=sin(_pitch)*cos(_yaw);
	_target.z=sin(_pitch)*sin(_yaw);
	_target.y=cos(_pitch);

	CalcViewMat();
}

void Camera::MoveLeft(float dTime)
{
	_eye -= dTime * glm::normalize(glm::cross(_target, _up));
	CalcViewMat();
}

void Camera::MoveRight(float dTime)
{
	_eye += dTime * glm::normalize(glm::cross(_target, _up));
	CalcViewMat();
}

void Camera::MoveForward(float dTime)
{
	_eye += dTime * glm::normalize(_target);
	CalcViewMat();
}

void Camera::MoveBackward(float dTime)
{
	_eye -= dTime * glm::normalize(_target);
	CalcViewMat();
}

void Camera::AddShader(Shader* shader)
{
	_shaders.push_back(shader);
	shader->UpdateCameraMatrices();
}

void Camera::RemoveShader(Shader* shader)
{
	_shaders.remove(shader);
}

void Camera::NotifyShaders()
{
	for (Shader* shader : _shaders)
	{
		shader->UpdateCameraMatrices();
	}
}
