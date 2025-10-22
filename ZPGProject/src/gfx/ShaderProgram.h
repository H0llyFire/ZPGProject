#pragma once
#include <memory>
#include <string>
#include <GL/glew.h>
#include <glm/ext/matrix_float4x4.hpp>

#include "Light.h"
#include "FragmentShader.h"
#include "VertexShader.h"
#include "../Observer.h"

class Camera;

class ShaderProgram : public Observer
{
private:
	std::shared_ptr<Camera> _camera;
	std::shared_ptr<Light> _light;
	GLuint _program;
	
	void Create(const std::shared_ptr<VertexShader>& vertShader, const std::shared_ptr<FragmentShader>& fragShader);
	void UpdateCamera() const;
	void UpdateLight() const;
public:
	ShaderProgram(const std::shared_ptr<Camera>& camera, const std::shared_ptr<VertexShader>& vertShader, const std::shared_ptr<FragmentShader>& fragShader);
	~ShaderProgram();
	
	void Bind() const;
	void Bind(glm::mat4 iMat) const;
	static void Unbind();

	void ChangeLight(const std::shared_ptr<Light>& light);

	void Notify() override;
	
};
