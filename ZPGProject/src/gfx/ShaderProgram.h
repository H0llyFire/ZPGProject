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
	
	void Bind() const;
	static void Unbind();
	
	void UpdateModelMatrix(glm::mat4 iMat) const;
	void UpdateLight(const Light* light, const std::string& index) const;
	void UpdatePointLightCount(int count) const;
	void UpdateSpotLightCount(int count) const;
	void UpdateDirectionalLightCount(int count) const;
	void UpdateAmbientLightCount(int count) const;
	void ApplyMaterial(glm::vec4 color, glm::vec3 reflectCoefficients, float shininess) const;

	void Notify(ObservableObject* sender, const ObservableArgs& args) override;
};
