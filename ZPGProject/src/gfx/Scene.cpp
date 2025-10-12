#include "Scene.h"

void Scene::AddObject(const DrawableObject& obj)
{
	_objects.push_back(obj);
}

void Scene::Draw(float dTime) const
{
	for (DrawableObject obj : _objects)
	{
		obj.Draw(dTime);
	}
}
