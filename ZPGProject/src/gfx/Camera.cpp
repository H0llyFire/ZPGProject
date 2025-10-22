#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"


void Camera::CalcViewMat()
{
	_viewMat = glm::lookAt(_eye, _eye+_target, _up);
	NotifyAll();
}

void Camera::CalcProjMat()
{
	_projMat = glm::perspective(glm::radians(60.f), _ratioWidth / _ratioHeight, 0.1f, 100.0f);
	NotifyAll();
}

Camera::Camera(float ratioWidth, float ratioHeight)
	: _eye(0.f, 0.f, 0.f), _target(0.f, 0.f, 0.f), _up(0.f, 1.f, 0.f), _ratioWidth(ratioWidth), _ratioHeight(ratioHeight)
{
	CalcProjMat();
	CalcViewMat();
}

Camera::Camera(float ratioWidth, float ratioHeight, const std::shared_ptr<Observer>& shader)
	: _eye(0.f, 0.f, 0.f), _target(0.f, 0.f, 0.f), _up(0.f, 1.f, 0.f), _ratioWidth(ratioWidth), _ratioHeight(ratioHeight)
{
	Attach(shader);
	CalcProjMat();
	CalcViewMat();
}

glm::mat4 Camera::GetCamera() const
{
	return _viewMat;
}

glm::vec3 Camera::GetPosition() const
{
	return _eye;
}

glm::mat4 Camera::GetProjection() const
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

	_target.x=sin(_pitch)*cos(_yaw);
	_target.z=sin(_pitch)*sin(_yaw);
	_target.y=cos(_pitch);

	CalcViewMat();
}

void Camera::MoveLeft(float dTime)
{
	_eye -= 2 * dTime * glm::normalize(glm::cross(_target, _up));
	CalcViewMat();
}

void Camera::MoveRight(float dTime)
{
	_eye += 2 * dTime * glm::normalize(glm::cross(_target, _up));
	CalcViewMat();
}

void Camera::MoveForward(float dTime)
{
	_eye += 2 * dTime * glm::normalize(_target);
	CalcViewMat();
}

void Camera::MoveBackward(float dTime)
{
	_eye -= 2 * dTime * glm::normalize(_target);
	CalcViewMat();
}

void Camera::MoveTo(float x, float y, float z)
{
	_eye.x = x;
	_eye.y = y;
	_eye.z = z;
	CalcViewMat();
}
