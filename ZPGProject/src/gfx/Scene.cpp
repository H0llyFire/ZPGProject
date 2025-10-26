#include "Scene.h"

#include <iostream>

#include "Camera.h"
#include "Light.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"

void Scene::AddObject(const std::shared_ptr<DrawableObject>& obj)
{
	if(obj->GetShader() != nullptr)
	{
		auto [it, inserted] = _activeShaders.insert(obj->GetShader());
		if(inserted)
		{
			it->get()->UpdateLightCount(_lights.size());
			for(const auto& [light, index] : _lightIndices)
				it->get()->UpdateLight(light, index);
			std::cout << "Active shaders count: " << _activeShaders.size() << "\n";
		}
	}
	_objects.push_back(obj);
}

void Scene::AddLight(const std::shared_ptr<Light>& light)
{
	_lights.push_back(light);
	AddObject(light);
	_lightIndices.insert(std::pair(light.get(), std::to_string(_lightIndices.size())));

	light->Attach(shared_from_this());
	for (const auto& shader : _activeShaders)
		shader->UpdateLightCount(_lights.size());
}

void Scene::SetCamera(const std::shared_ptr<Camera>& camera)
{
	_camera = camera;
}

void Scene::Draw(float dTime) const
{
	for (const std::shared_ptr<DrawableObject>& obj : _objects)
	{
		obj->Update(dTime);
		obj->Draw(dTime);
	}
}

void Scene::Notify(ObservableObject* sender, const ObservableArgs& args)
{
	if(Light* light = dynamic_cast<Light*>(sender))
	{
		for (const auto& shader : _activeShaders)
		{
			shader->UpdateLight(light, _lightIndices.find(light)->second);
		}
	}
	else if(Camera* camera = dynamic_cast<Camera*>(sender))
	{
	}
}
