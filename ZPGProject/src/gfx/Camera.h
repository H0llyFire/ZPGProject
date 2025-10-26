#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include "../ObservableObject.h"

class Shader;
class Observer;

class Camera : public ObservableObject
{
private:
    glm::vec3 _eye, _target, _up;
	glm::mat4 _viewMat, _projMat;
	float _ratioWidth, _ratioHeight, _fov;
	float _yaw = 0.f, _pitch = 0.f;

	void CalcViewMat();
	void CalcProjMat();
public:
	Camera(float ratioWidth, float ratioHeight, float fov);
	Camera(float ratioWidth, float ratioHeight, float fov, const std::shared_ptr<Observer>& shader);

	glm::mat4 GetCamera() const;
	glm::vec3 GetPosition() const;
	glm::mat4 GetProjection() const;

	void UpdateProjection(float width, float height);
	void UpdateFOV(float fov);

	void CalcTarget(float yaw, float pitch);

    void MoveLeft(float dTime);
	void MoveRight(float dTime);
	void MoveForward(float dTime);
	void MoveBackward(float dTime);
	void MoveTo(float x, float y, float z);
};
