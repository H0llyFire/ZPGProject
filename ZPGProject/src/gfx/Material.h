#pragma once
#include <memory>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class ShaderProgram;

class Material
{
private:
	float _shininess;
	glm::vec4 _color;
	glm::vec3 _reflectCoefficients;
public:
	Material(glm::vec4 color, glm::vec3 reflectCoefficients, float shininess);

	void Apply(const std::shared_ptr<ShaderProgram>& shader) const;
};
