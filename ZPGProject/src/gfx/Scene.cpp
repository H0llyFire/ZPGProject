#include "Scene.h"

void Scene::AddObject(const std::shared_ptr<DrawableObject>& obj)
{
	_objects.push_back(obj);
}

void Scene::AddLight(const std::shared_ptr<Light>& light)
{
	_lights.push_back(light);
}

void Scene::Draw(float dTime) const
{
	for (const std::shared_ptr<DrawableObject>& obj : _objects)
	{
		obj->Draw(dTime);
	}
}
