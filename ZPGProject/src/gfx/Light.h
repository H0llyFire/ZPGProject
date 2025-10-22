#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "../ObservableObject.h"

class Light : public ObservableObject
{
private:
    glm::vec3 _pos, _vec;
	glm::vec4 _color;
public:
	Light();
	Light(glm::vec3 pos);
	Light(glm::vec3 pos, glm::vec4 color);
	
	glm::vec3 GetPosition() const;
	glm::vec4 GetColor() const;
	
};
