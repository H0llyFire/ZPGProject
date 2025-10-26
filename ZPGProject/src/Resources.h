#pragma once
#include "ResourceManager.h"

class VertexShader;
class FragmentShader;
class ShaderProgram;
class Model;
class Scene;
class Camera;
class Light;
class DrawableObject;
class TransformComponent;
class TransformComposite;

class Resources
{
private:
	ResourceManager<VertexShader> _vertexShaderManager;
	ResourceManager<FragmentShader> _fragmentShaderManager;
	ResourceManager<ShaderProgram> _shaderManager;

	ResourceManager<Model> _modelManager;
	ResourceManager<Scene> _sceneManager;

	//These should be managed by the Scene (Sharing these between scenes is too much pain)
	ResourceManager<Camera> _cameraManager;
	ResourceManager<Light> _lightManager;
	ResourceManager<DrawableObject> _drawableObjectManager;

	//These should be managed by the DrawableObject (Sharing these between objects is too much pain)
	ResourceManager<TransformComponent> _transformComponentManager;
	ResourceManager<TransformComposite> _transformCompositeManager;
	
	std::shared_ptr<VertexShader> CreateVertexShader(const std::string& name);
	std::shared_ptr<FragmentShader> CreateFragmentShader(const std::string& name);
	std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& name, const std::string& cameraName, const std::string& vertexShaderName, const std::string& fragmentShaderName);
	std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& name, const std::string& cameraName);

	std::shared_ptr<Model> CreateModel(const std::string& name, const float* points, int count);
	std::shared_ptr<DrawableObject> CreateDrawableObject(const std::string& name, const std::string& modelName, const std::string& shaderName, const std::string& transformName);
	std::shared_ptr<DrawableObject> CreateDrawableObject(const std::string& name, const std::string& modelName, const std::string& shaderName, const std::shared_ptr<TransformComposite>& transform);

	std::shared_ptr<Camera> CreateCamera(const std::string& name, float width, float height, float fov);
	std::shared_ptr<Light> CreateLight(const std::string& name, std::shared_ptr<TransformComposite>& transform, glm::vec4 color, glm::vec4 specularColor);

public:
	Resources() = default;

	void InitModels();
	void InitShaders(const std::string& mainCam);
	std::shared_ptr<Camera> InitCamera(float windowWidth, float windowHeight, float fov);
	void InitScenes();

	void InitScene1();
	void InitScene2();
	void InitScene3();
	void InitScene4();

	std::shared_ptr<Scene> EnableScene(const std::string& name);
	void UpdateWindowSize(float width, float height);
	void UpdateCameraFOV(const std::string& name, float fov);
};
