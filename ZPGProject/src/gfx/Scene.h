#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../Observer.h"

class TextureUnitManager;
class FlashLight;
class AmbientLight;
class DirectionalLight;
class SpotLight;
class PointLight;
class Light;
class Camera;
class DrawableObject;
class ShaderProgram;

//There should always be only one active scene
class Scene: public Observer, public std::enable_shared_from_this<Scene>
{
private:
	std::unordered_set<std::shared_ptr<ShaderProgram>> _activeShaders;
	std::shared_ptr<Camera> _camera;
	std::vector<std::shared_ptr<DrawableObject>> _objects;

	std::vector<std::shared_ptr<PointLight>> _pointLights;
	std::unordered_map<PointLight*, std::string> _pointLightIndices;

	std::vector<std::shared_ptr<SpotLight>> _spotLights;
	std::unordered_map<SpotLight*, std::string> _spotLightIndices;
	
	std::vector<std::shared_ptr<DirectionalLight>> _directionalLights;
	std::unordered_map<DirectionalLight*, std::string> _directionalLightIndices;
	
	std::vector<std::shared_ptr<AmbientLight>> _ambientLights;
	std::unordered_map<AmbientLight*, std::string> _ambientLightIndices;
public:
	Scene() = default;

	void AddObject(const std::shared_ptr<DrawableObject>& obj);
	void AddLight(const std::shared_ptr<Light>& light);
	void AddLight(const std::shared_ptr<PointLight>& light);
	void AddLight(const std::shared_ptr<SpotLight>& light);
	void AddLight(const std::shared_ptr<DirectionalLight>& light);
	void AddLight(const std::shared_ptr<AmbientLight>& light);
	void AddLight(const std::shared_ptr<FlashLight>& light);
	void SetCamera(const std::shared_ptr<Camera>& camera);
	void Draw(float dTime, std::shared_ptr<TextureUnitManager> tuMngr) const;
	void Enable();


	void Notify(ObservableObject* sender, const ObservableArgs& args) override;
};
