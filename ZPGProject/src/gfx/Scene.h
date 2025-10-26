#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../Observer.h"

class Light;
class Camera;
class DrawableObject;
class ShaderProgram;

//There should always be only one active scene
class Scene: public Observer, public std::enable_shared_from_this<Scene>
{
private:
	std::vector<std::shared_ptr<DrawableObject>> _objects;
	std::vector<std::shared_ptr<Light>> _lights;
	std::unordered_map<Light*, std::string> _lightIndices;
	std::unordered_set<std::shared_ptr<ShaderProgram>> _activeShaders;
	std::shared_ptr<Camera> _camera;
public:
	Scene() = default;

	void AddObject(const std::shared_ptr<DrawableObject>& obj);
	void AddLight(const std::shared_ptr<Light>& light);
	void SetCamera(const std::shared_ptr<Camera>& camera);
	void Draw(float dTime) const;

	void Notify(ObservableObject* sender, const ObservableArgs& args) override;
};
