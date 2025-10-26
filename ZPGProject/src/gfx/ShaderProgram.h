#pragma once
#include <memory>
#include <string>

#include <GL/glew.h>
#include <glm/ext/matrix_float4x4.hpp>

#include "../Observer.h"

class Camera;
class Light;
class FragmentShader;
class VertexShader;

class ShaderProgram : public Observer
{
private:
	std::shared_ptr<Camera> _camera;
	GLuint _program;
	
	void Create(const std::shared_ptr<VertexShader>& vertShader, const std::shared_ptr<FragmentShader>& fragShader);
	void UpdateCamera() const;
	//void UpdateLight() const;
public:
	ShaderProgram(const std::shared_ptr<Camera>& camera, const std::shared_ptr<VertexShader>& vertShader, const std::shared_ptr<FragmentShader>& fragShader);
	~ShaderProgram();
	
	void Bind(glm::mat4 iMat) const;
	static void Unbind();

	//void ChangeLight(const std::shared_ptr<Light>& light);
	void UpdateLight(const Light* light, const std::string& index) const;
	void UpdateLightCount(int count) const;

	void Notify(ObservableObject* sender, const ObservableArgs& args) override;
};
