#pragma once
#include <vector>

#include "DrawableObject.h"

class Scene
{
private:
	std::vector<std::shared_ptr<DrawableObject>> _objects;
	std::vector<std::shared_ptr<Light>> _lights;
public:
	Scene() = default;

	void AddObject(const std::shared_ptr<DrawableObject>& obj);
	void AddLight(const std::shared_ptr<Light>& light);
	void Draw(float dTime) const;
};
