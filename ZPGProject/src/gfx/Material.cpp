#include "Material.h"

#include "ShaderProgram.h"

Material::Material(glm::vec4 color, glm::vec3 reflectCoefficients, float shininess)
	: _shininess(shininess), _color(color), _reflectCoefficients(reflectCoefficients)
{
}

void Material::Apply(const std::shared_ptr<ShaderProgram>& shader) const
{
	shader->ApplyMaterial(_color, _reflectCoefficients, _shininess);
}
