#pragma once
#include "ResourceManager.h"
#include "gfx/DrawableObject.h"
#include "gfx/FragmentShader.h"
#include "gfx/Scene.h"
#include "gfx/VertexShader.h"
#include "gfx/Camera.h"

class Resources
{
private:
	ResourceManager<VertexShader> _vertexShaderManager;

	ResourceManager<FragmentShader> _fragmentShaderManager;
	ResourceManager<ShaderProgram> _shaderManager;
	ResourceManager<Camera> _cameraManager;
	ResourceManager<DrawableObject> _drawableObjectManager;
	ResourceManager<Model> _modelManager;
	ResourceManager<Scene> _sceneManager;
	ResourceManager<Light> _lightManager;

	ResourceManager<TransformComponent> _transformComponentManager;
	ResourceManager<TransformComposite> _transformCompositeManager;
	
	std::shared_ptr<VertexShader> CreateVertexShader(const std::string& name);
	std::shared_ptr<FragmentShader> CreateFragmentShader(const std::string& name);
	std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& name, const std::string& cameraName, const std::string& vertexShaderName, const std::string& fragmentShaderName);
	std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& name, const std::string& cameraName);

	std::shared_ptr<Model> CreateModel(const std::string& name, const float* points, int count);
	std::shared_ptr<DrawableObject> CreateDrawableObject(const std::string& name, const std::string& modelName, const std::string& shaderName, const std::string& transformName);
	std::shared_ptr<DrawableObject> CreateDrawableObject(const std::string& name, const std::string& modelName, const std::string& shaderName, const std::shared_ptr<TransformComposite>& transform);

	std::shared_ptr<Camera> CreateCamera(const std::string& name, float width, float height);
	std::shared_ptr<Light> CreateLight(const std::string& name, glm::vec3 position, glm::vec4 color);

public:
	Resources() = default;

	void InitModels();
	void InitShaders(const std::string& mainCam);
	std::shared_ptr<Camera> InitCamera(float windowWidth, float windowHeight);
	void InitScenes();

	void InitScene1();
	void InitScene2();
	void InitScene3();
	void InitScene4();

	std::shared_ptr<Scene> EnableScene(const std::string& name);
};
