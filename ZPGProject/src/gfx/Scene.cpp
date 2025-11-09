#include "Scene.h"

#include <iostream>

#include "Camera.h"
#include "lights/PointLight.h"
#include "lights/SpotLight.h"
#include "lights/DirectionalLight.h"
#include "lights/AmbientLight.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "lights/FlashLight.h"

void Scene::AddObject(const std::shared_ptr<DrawableObject>& obj)
{
	if(obj->GetShader() != nullptr)
	{
		auto [it, inserted] = _activeShaders.insert(obj->GetShader());
		if(inserted)
		{
			it->get()->UpdatePointLightCount(_pointLights.size());
			it->get()->UpdateSpotLightCount(_spotLights.size());
			it->get()->UpdateDirectionalLightCount(_directionalLights.size());
			it->get()->UpdateAmbientLightCount(_ambientLights.size());

			for(const auto& [light, index] : _pointLightIndices)
				it->get()->UpdateLight(light, index);
			for(const auto& [light, index] : _spotLightIndices)
				it->get()->UpdateLight(light, index);
			for(const auto& [light, index] : _directionalLightIndices)
				it->get()->UpdateLight(light, index);
			for(const auto& [light, index] : _ambientLightIndices)
				it->get()->UpdateLight(light, index);


			std::cout << "Active shaders count: " << _activeShaders.size() << "\n";
		}
	}
	_objects.push_back(obj);
}

void Scene::AddLight(const std::shared_ptr<Light>& light)
{
	if(auto pl = std::dynamic_pointer_cast<PointLight>(light))
		AddLight(pl);
	else if(auto sl =  std::dynamic_pointer_cast<SpotLight>(light))
		AddLight(sl);
	else if(auto dl =  std::dynamic_pointer_cast<DirectionalLight>(light))
		AddLight(dl);
	else if(auto al =  std::dynamic_pointer_cast<AmbientLight>(light))
		AddLight(al);
	else if (auto fl =  std::dynamic_pointer_cast<FlashLight>(light))
		AddLight(std::static_pointer_cast<SpotLight>(fl));
}

void Scene::AddLight(const std::shared_ptr<PointLight>& light)
{
	_pointLights.push_back(light);
	_pointLightIndices.insert(std::pair(light.get(), std::to_string(_pointLightIndices.size())));
	AddObject(light);

	light->Attach(shared_from_this());
	for (const auto& shader : _activeShaders)
		shader->UpdatePointLightCount(_pointLights.size());
}

void Scene::AddLight(const std::shared_ptr<SpotLight>& light)
{
	_spotLights.push_back(light);
	_spotLightIndices.insert(std::pair(light.get(), std::to_string(_spotLightIndices.size())));
	AddObject(light);
	
	light->Attach(shared_from_this());
	for (const auto& shader : _activeShaders)
		shader->UpdateSpotLightCount(_spotLights.size());
}

void Scene::AddLight(const std::shared_ptr<DirectionalLight>& light)
{
	_directionalLights.push_back(light);
	_directionalLightIndices.insert(std::pair(light.get(), std::to_string(_directionalLightIndices.size())));
	AddObject(light);

	light->Attach(shared_from_this());
	for (const auto& shader : _activeShaders)
		shader->UpdateDirectionalLightCount(_directionalLights.size());
}

void Scene::AddLight(const std::shared_ptr<AmbientLight>& light)
{
	_ambientLights.push_back(light);
	_ambientLightIndices.insert(std::pair(light.get(), std::to_string(_ambientLightIndices.size())));
	AddObject(light);

	light->Attach(shared_from_this());
	for (const auto& shader : _activeShaders)
		shader->UpdateAmbientLightCount(_ambientLights.size());
}

void Scene::AddLight(const std::shared_ptr<FlashLight>& light)
{
	AddLight(std::shared_ptr<SpotLight>(light));
}

void Scene::SetCamera(const std::shared_ptr<Camera>& camera)
{
	_camera = camera;
}

void Scene::Draw(float dTime, std::shared_ptr<TextureUnitManager> tuMngr) const
{
	for (const std::shared_ptr<DrawableObject>& obj : _objects)
	{
		obj->Update(dTime);
		obj->Draw(dTime, tuMngr);
	}
}

void Scene::Enable()
{
	for (const auto& shader : _activeShaders)
		shader->UpdatePointLightCount(_pointLights.size());
	for (const auto& shader : _activeShaders)
		shader->UpdateSpotLightCount(_spotLights.size());
	for (const auto& shader : _activeShaders)
		shader->UpdateAmbientLightCount(_ambientLights.size());
	for (const auto& shader : _activeShaders)
		shader->UpdateDirectionalLightCount(_directionalLights.size());

	for (const auto& shader : _activeShaders)
	{
		for(const auto& [light, index] : _pointLightIndices)
			shader->UpdateLight(light, index);
		for(const auto& [light, index] : _spotLightIndices)
			shader->UpdateLight(light, index);
		for(const auto& [light, index] : _directionalLightIndices)
			shader->UpdateLight(light, index);
		for(const auto& [light, index] : _ambientLightIndices)
			shader->UpdateLight(light, index);
	}
}

void Scene::Notify(ObservableObject* sender, const ObservableArgs& args)
{
	if(Light* light = dynamic_cast<Light*>(sender))
	{
		if(PointLight* pl = dynamic_cast<PointLight*>(light))
			for (const auto& shader : _activeShaders)
				shader->UpdateLight(light, _pointLightIndices.find(pl)->second);

		else if(SpotLight* sl = dynamic_cast<SpotLight*>(light))
			for (const auto& shader : _activeShaders)
				shader->UpdateLight(light, _spotLightIndices.find(sl)->second);

		else if(DirectionalLight* dl = dynamic_cast<DirectionalLight*>(light))
			for (const auto& shader : _activeShaders)
				shader->UpdateLight(light, _directionalLightIndices.find(dl)->second);

		else if(AmbientLight* al = dynamic_cast<AmbientLight*>(light))
			for (const auto& shader : _activeShaders)
				shader->UpdateLight(light, _ambientLightIndices.find(al)->second);
	}
}
