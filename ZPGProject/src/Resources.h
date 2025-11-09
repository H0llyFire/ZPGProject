#pragma once
#include "ResourceManager.h"

class FlashLight;
class AmbientLight;
class DirectionalLight;
class SpotLight;
class PointLight;
class VertexShader;
class FragmentShader;
class ShaderProgram;
class Model;
class Material;
class Texture;
class Scene;
class Camera;
class Light;
class DrawableObject;
class TransformComponent;
class TransformComposite;

class Resources
{
private:
#pragma region Resource Managers
	//-----------------------------------------------------------------------------------------------
	//--------------------------------Resource Managers----------------------------------------------
	//-----------------------------------------------------------------------------------------------

	ResourceManager<VertexShader> _vertexShaderManager;
	ResourceManager<FragmentShader> _fragmentShaderManager;
	ResourceManager<ShaderProgram> _shaderManager;

	ResourceManager<Model> _modelManager;
	ResourceManager<Material> _materialManager;
	ResourceManager<Texture> _textureManager;
	ResourceManager<Scene> _sceneManager;

	//These should be managed by the Scene (Sharing these between scenes is too much pain)
	ResourceManager<Camera> _cameraManager;
	ResourceManager<DrawableObject> _drawableObjectManager;

	ResourceManager<PointLight> _pointLightManager;
	ResourceManager<DirectionalLight> _directionalLightManager;
	ResourceManager<SpotLight> _spotLightManager;
	ResourceManager<AmbientLight> _ambientLightManager;
	ResourceManager<FlashLight> _flashLightManager;

	//These should be managed by the DrawableObject (Sharing these between objects is too much pain)
	ResourceManager<TransformComponent> _transformComponentManager;
	ResourceManager<TransformComposite> _transformCompositeManager;
#pragma endregion

#pragma region Creation Methods
	//-----------------------------------------------------------------------------------------------
	//--------------------------------Creation Methods-----------------------------------------------
	//-----------------------------------------------------------------------------------------------

	std::shared_ptr<VertexShader> CreateVertexShader(
		const std::string& name);

	std::shared_ptr<FragmentShader> CreateFragmentShader(
		const std::string& name);

	std::shared_ptr<ShaderProgram> CreateShaderProgram(
		const std::string& name, 
		const std::string& cameraName, 
		const std::string& vertexShaderName, 
		const std::string& fragmentShaderName);

	std::shared_ptr<ShaderProgram> CreateShaderProgram(
		const std::string& name, 
		const std::string& cameraName);

	std::shared_ptr<Model> CreateModel(
		const std::string& name, 
		const float* points, 
		int count, 
		int groupSize = 6);

	std::shared_ptr<Model> CreateModel(
		const std::string& name, 
		const std::string& modelFileName,
		const std::string& modelExtraPath = "");

	std::shared_ptr<DrawableObject> CreateDrawableObject(
		const std::string& name, 
		const std::string& modelName, 
		const std::string& shaderName, 
		const std::string& transformName);

	std::shared_ptr<DrawableObject> CreateDrawableObject(
		const std::string& name, 
		const std::string& modelName, 
		const std::string& shaderName, 
		const std::shared_ptr<TransformComposite>& transform);

	std::shared_ptr<DrawableObject> CreateDrawableObject(
		const std::string& name, 
		const std::shared_ptr<Model>& model, 
		const std::shared_ptr<ShaderProgram>& shader, 
		const std::shared_ptr<TransformComposite>& transform);

	std::shared_ptr<DrawableObject> CreateDrawableObject(
		const std::string& name, 
		const std::string& modelName, 
		const std::string& shaderName,
		const std::string& materialName,
		const std::shared_ptr<TransformComposite>& transform);
		
	std::shared_ptr<DrawableObject> CreateDrawableObject(
		const std::string& name, 
		const std::shared_ptr<Model>& model, 
		const std::shared_ptr<ShaderProgram>& shader,
		const std::shared_ptr<Material>& material,
		const std::shared_ptr<TransformComposite>& transform);

	std::shared_ptr<DrawableObject> CreateDrawableObject(
		const std::string& name, 
		const std::shared_ptr<TransformComposite>& transform,
		const std::shared_ptr<Model>& model, 
		const std::shared_ptr<ShaderProgram>& shader = nullptr,
		const std::shared_ptr<Material>& material = nullptr,
		const std::shared_ptr<Texture>& texture = nullptr);

	std::shared_ptr<DrawableObject> CreateDrawableObject(
		const std::string& name, 
		const std::shared_ptr<TransformComposite>& transform,
		const std::string& modelName, 
		const std::string& shaderName = "",
		const std::string& materialName = "",
		const std::string& textureName = "");

	std::shared_ptr<Camera> CreateCamera(
		const std::string& name, 
		float width, 
		float height, 
		float fov);
	
	std::shared_ptr<PointLight> CreatePointLight(
		const std::string& name, 
		const std::string& modelName, 
		const std::string& shaderName,
		const std::shared_ptr<TransformComposite>& transform, 
		const glm::vec4 color, 
		const glm::vec4 specularColor,
		const glm::vec3 attenuationFactors);

	std::shared_ptr<PointLight> CreatePointLight(
		const std::string& name, 
		const std::shared_ptr<Model>& model, 
		const std::shared_ptr<ShaderProgram>& shader,
		const std::shared_ptr<TransformComposite>& transform, 
		const glm::vec4 color, 
		const glm::vec4 specularColor,
		const glm::vec3 attenuationFactors);
	
	std::shared_ptr<PointLight> CreatePointLight(
		const std::string& name, 
		const std::shared_ptr<TransformComposite>& transform, 
		const glm::vec4 color, 
		const glm::vec4 specularColor,
		const glm::vec3 attenuationFactors);
	
	std::shared_ptr<SpotLight> CreateSpotLight(
		const std::string& name, 
		const std::string& modelName, 
		const std::string& shaderName,
		const std::shared_ptr<TransformComposite>& transform, 
		const glm::vec4 color, 
		const glm::vec4 specularColor,
		const glm::vec3 attenuationFactors,
		const glm::vec3 direction,
		float innerCutoff,
		float outerCutoff);

	std::shared_ptr<SpotLight> CreateSpotLight(
		const std::string& name, 
		const std::shared_ptr<Model>& model, 
		const std::shared_ptr<ShaderProgram>& shader,
		const std::shared_ptr<TransformComposite>& transform, 
		const glm::vec4 color, 
		const glm::vec4 specularColor,
		const glm::vec3 attenuationFactors,
		const glm::vec3 direction,
		float innerCutoff,
		float outerCutoff);

	std::shared_ptr<SpotLight> CreateSpotLight(
		const std::string& name, 
		const std::shared_ptr<TransformComposite>& transform, 
		const glm::vec4 color, 
		const glm::vec4 specularColor,
		const glm::vec3 attenuationFactors,
		const glm::vec3 direction,
		float innerCutoff,
		float outerCutoff);

	std::shared_ptr<DirectionalLight> CreateDirectionalLight(
		const std::string& name, 
		const glm::vec4 color, 
		const glm::vec4 specularColor,
		const glm::vec3 direction);

	std::shared_ptr<AmbientLight> CreateAmbientLight(
		const std::string& name, 
		const glm::vec4 color);

	std::shared_ptr<FlashLight> CreateFlashLight(
		const std::string& name,
		const std::string& modelName,
		const std::string& shaderName,
		const std::shared_ptr<TransformComposite>& transform,
		const glm::vec4 color,
		const glm::vec4 specularColor,
		const glm::vec3 attenuationFactors,
		float innerCutoff,
		float outerCutoff);

	std::shared_ptr<FlashLight> CreateFlashLight(
		const std::string& name,
		const std::shared_ptr<Model>& model,
		const std::shared_ptr<ShaderProgram>& shader,
		const std::shared_ptr<TransformComposite>& transform,
		const glm::vec4 color,
		const glm::vec4 specularColor,
		const glm::vec3 attenuationFactors,
		float innerCutoff,
		float outerCutoff);

	std::shared_ptr<FlashLight> CreateFlashLight(
		const std::string& name,
		const std::shared_ptr<TransformComposite>& transform,
		const glm::vec4 color,
		const glm::vec4 specularColor,
		const glm::vec3 attenuationFactors,
		float innerCutoff,
		float outerCutoff);

	std::shared_ptr<Material> CreateMaterial(
		const std::string& name,
		glm::vec4 color,
		glm::vec3 reflectCoefficients,
		float shininess);
#pragma endregion

public:
	Resources() = default;

	void InitModels();
	void InitShaders(const std::string& mainCam);
	void InitMaterials();
	void InitTextures();
	std::shared_ptr<Camera> InitMainCamera(float windowWidth, float windowHeight, float fov);
	std::shared_ptr<FlashLight> InitMainFlashLight();
	void InitScenes();

	void InitScene1();
	void InitScene2();
	void InitScene3();
	void InitScene4();
	void InitScene5();

	std::shared_ptr<Scene> EnableScene(const std::string& name);
	void UpdateWindowSize(float width, float height);
	void UpdateCameraFOV(const std::string& name, float fov);
};