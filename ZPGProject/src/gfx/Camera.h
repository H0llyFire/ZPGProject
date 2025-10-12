#pragma once
#include <list>
#include <glm/ext/matrix_float4x4.hpp>

class Shader;

class Camera
{
private:
    std::list<Shader*> _shaders;
    glm::vec3 _eye, _target, _up;
	glm::mat4 _viewMat, _projMat;
	float _ratioWidth, _ratioHeight;
	float _yaw = 0.f, _pitch = 0.f;

	void CalcViewMat();
	void CalcProjMat();
public:
	Camera(float ratioWidth, float ratioHeight);
	Camera(float ratioWidth, float ratioHeight, Shader* shader);

	glm::mat4 GetCamera();
	glm::mat4 GetProjection();


	void CalcTarget(float yaw, float pitch);

    void MoveLeft(float dTime);
	void MoveRight(float dTime);
	void MoveForward(float dTime);
	void MoveBackward(float dTime);

	void AddShader(Shader* shader);
	void RemoveShader(Shader* shader);
	void NotifyShaders();
};
