#pragma once
#include <vector>

#include "DrawableObject.h"

class Scene
{
private:
	std::vector<DrawableObject> _objects;
public:
	Scene() = default;

	void AddObject(const DrawableObject& obj);
	void Draw(float dTime) const;
};
