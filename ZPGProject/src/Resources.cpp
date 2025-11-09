#pragma region Includes
#include "Resources.h"

#include <iostream>

#include "gfx/models/bushes.h"
#include "gfx/models/gift.h"
#include "gfx/models/plain.h"
#include "gfx/models/sphere.h"
#include "gfx/models/suzi_flat.h"
#include "gfx/models/suzi_smooth.h"
#include "gfx/models/tree.h"

#include "gfx/trans/TransformComponent.h"
#include "gfx/trans/TransformComposite.h"
#include "gfx/trans/Translate.h"
#include "gfx/trans/Scale.h"
#include "gfx/trans/Rotate.h"
#include "gfx/trans/RotateTime.h"
#include "gfx/trans/TranslateRandom.h"
#include "gfx/trans/FollowCamera.h"

#include "gfx/gfxHelpers/FragmentShader.h"
#include "gfx/gfxHelpers/VertexShader.h"

#include "gfx/lights/PointLight.h"
#include "gfx/lights/SpotLight.h"
#include "gfx/lights/DirectionalLight.h"
#include "gfx/lights/AmbientLight.h"
#include "gfx/lights/FlashLight.h"

#include "gfx/Camera.h"
#include "gfx/DrawableObject.h"
#include "gfx/Model.h"
#include "gfx/Material.h"
#include "gfx/Scene.h"
#include "gfx/ShaderProgram.h"
#pragma endregion

#pragma region Creation Methods
std::shared_ptr<VertexShader> Resources::CreateVertexShader(const std::string& name)
{
	return _vertexShaderManager.Add(name, name);
}
std::shared_ptr<FragmentShader> Resources::CreateFragmentShader(const std::string& name)
{
	return _fragmentShaderManager.Add(name, name);
}
std::shared_ptr<ShaderProgram> Resources::CreateShaderProgram(const std::string& name, const std::string& cameraName, 
	const std::string& vertexShaderName, const std::string& fragmentShaderName)
{
	auto sp = _shaderManager.Add(name, _cameraManager.Get(cameraName), _vertexShaderManager.Add(vertexShaderName, vertexShaderName), _fragmentShaderManager.Add(fragmentShaderName, fragmentShaderName));
	_cameraManager.Get(cameraName)->Attach(sp);
	return sp;
}
std::shared_ptr<ShaderProgram> Resources::CreateShaderProgram(const std::string& name, const std::string& cameraName)
{
	auto sp = _shaderManager.Add(name, _cameraManager.Get(cameraName), _vertexShaderManager.Add(name, name), _fragmentShaderManager.Add(name, name));
	_cameraManager.Get(cameraName)->Attach(sp);
	return sp;
}
std::shared_ptr<Model> Resources::CreateModel(const std::string& name, const float* points, int count)
{
	return _modelManager.Add(name, points, count);
}
std::shared_ptr<Model> Resources::CreateModel(const std::string& name, const std::string& modelFileName)
{
	return _modelManager.Add(name, modelFileName);
}
std::shared_ptr<DrawableObject> Resources::CreateDrawableObject(const std::string& name, const std::string& modelName,
    const std::string& shaderName, const std::string& transformName)
{
	return _drawableObjectManager.Add(name, _modelManager.Get(modelName), _shaderManager.Get(shaderName), _transformCompositeManager.Get(transformName));
}
std::shared_ptr<DrawableObject> Resources::CreateDrawableObject(const std::string& name, const std::string& modelName,
	const std::string& shaderName, const std::shared_ptr<TransformComposite>& transform)
{
	return _drawableObjectManager.Add(name, _modelManager.Get(modelName), _shaderManager.Get(shaderName), transform);
}

std::shared_ptr<DrawableObject> Resources::CreateDrawableObject(const std::string& name,
	const std::shared_ptr<Model>& model, const std::shared_ptr<ShaderProgram>& shader,
	const std::shared_ptr<TransformComposite>& transform)
{
	return _drawableObjectManager.Add(name, model, shader, transform);
}

std::shared_ptr<DrawableObject> Resources::CreateDrawableObject(const std::string& name, const std::string& modelName,
	const std::string& shaderName, const std::string& materialName, const std::shared_ptr<TransformComposite>& transform)
{
	return _drawableObjectManager.Add(name, _modelManager.Get(modelName), _shaderManager.Get(shaderName),
		transform, _materialManager.Get(materialName));
}

std::shared_ptr<DrawableObject> Resources::CreateDrawableObject(const std::string& name,
	const std::shared_ptr<Model>& model, const std::shared_ptr<ShaderProgram>& shader,
	const std::shared_ptr<Material>& material, const std::shared_ptr<TransformComposite>& transform)
{
	return _drawableObjectManager.Add(name, model, shader, transform, material);
}

std::shared_ptr<Camera> Resources::CreateCamera(const std::string& name, float width, float height, float fov)
{
	return _cameraManager.Add(name, width, height, fov);
}

//TODO: Add materials to lights with drawable objects
std::shared_ptr<PointLight> Resources::CreatePointLight(const std::string& name, const std::string& modelName,
	const std::string& shaderName, const std::shared_ptr<TransformComposite>& transform, const glm::vec4 color,
	const glm::vec4 specularColor, const glm::vec3 attenuationFactors)
{
	return _pointLightManager.Add<PointLight>(name, _modelManager.Get(modelName), _shaderManager.Get(shaderName), transform, color, specularColor, attenuationFactors);
}

std::shared_ptr<PointLight> Resources::CreatePointLight(const std::string& name, const std::shared_ptr<Model>& model,
	const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<TransformComposite>& transform,
	const glm::vec4 color, const glm::vec4 specularColor, const glm::vec3 attenuationFactors)
{
	return _pointLightManager.Add<PointLight>(name, model, shader, transform, color, specularColor, attenuationFactors);
}

std::shared_ptr<PointLight> Resources::CreatePointLight(const std::string& name,
	const std::shared_ptr<TransformComposite>& transform, const glm::vec4 color, const glm::vec4 specularColor,
	const glm::vec3 attenuationFactors)
{
	return _pointLightManager.Add<PointLight>(name, transform, color, specularColor, attenuationFactors);
}

std::shared_ptr<SpotLight> Resources::CreateSpotLight(const std::string& name, const std::string& modelName,
	const std::string& shaderName, const std::shared_ptr<TransformComposite>& transform, const glm::vec4 color,
	const glm::vec4 specularColor, const glm::vec3 attenuationFactors, const glm::vec3 direction, float innerCutoff, float outerCutoff)
{
	return _spotLightManager.Add<SpotLight>(name, _modelManager.Get(modelName), _shaderManager.Get(shaderName), transform,
		color, direction, innerCutoff, outerCutoff, specularColor, attenuationFactors);
}

std::shared_ptr<SpotLight> Resources::CreateSpotLight(const std::string& name, const std::shared_ptr<Model>& model,
	const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<TransformComposite>& transform,
	const glm::vec4 color, const glm::vec4 specularColor, const glm::vec3 attenuationFactors, const glm::vec3 direction,
	float innerCutoff, float outerCutoff)
{
	return _spotLightManager.Add<SpotLight>(name, model, shader, transform,
		color, direction, innerCutoff, outerCutoff, specularColor, attenuationFactors);
}

std::shared_ptr<SpotLight> Resources::CreateSpotLight(const std::string& name,
	const std::shared_ptr<TransformComposite>& transform, const glm::vec4 color, const glm::vec4 specularColor,
	const glm::vec3 attenuationFactors, const glm::vec3 direction, float innerCutoff, float outerCutoff)
{
	return _spotLightManager.Add<SpotLight>(name, transform,
		color, direction, innerCutoff, outerCutoff, specularColor, attenuationFactors);
}

std::shared_ptr<DirectionalLight> Resources::CreateDirectionalLight(const std::string& name, const glm::vec4 color,
	const glm::vec4 specularColor, const glm::vec3 direction)
{
	return _directionalLightManager.Add<DirectionalLight>(name, direction, color, specularColor);
}

std::shared_ptr<AmbientLight> Resources::CreateAmbientLight(const std::string& name, const glm::vec4 color)
{
	return _ambientLightManager.Add<AmbientLight>(name, color);
}

std::shared_ptr<FlashLight> Resources::CreateFlashLight(const std::string& name, const std::string& modelName,
	const std::string& shaderName, const std::shared_ptr<TransformComposite>& transform, const glm::vec4 color,
	const glm::vec4 specularColor, const glm::vec3 attenuationFactors, float innerCutoff, float outerCutoff)
{
	return _flashLightManager.Add(name, _modelManager.Get(modelName), _shaderManager.Get(shaderName), transform,
		color, innerCutoff, outerCutoff, specularColor, attenuationFactors);
}

std::shared_ptr<FlashLight> Resources::CreateFlashLight(const std::string& name, const std::shared_ptr<Model>& model,
	const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<TransformComposite>& transform,
	const glm::vec4 color, const glm::vec4 specularColor, const glm::vec3 attenuationFactors,
	float innerCutoff, float outerCutoff)
{
	return _flashLightManager.Add(name, model, shader, transform,
		color, innerCutoff, outerCutoff, specularColor, attenuationFactors);
}

std::shared_ptr<FlashLight> Resources::CreateFlashLight(const std::string& name,
	const std::shared_ptr<TransformComposite>& transform, const glm::vec4 color, const glm::vec4 specularColor,
	const glm::vec3 attenuationFactors, float innerCutoff, float outerCutoff)
{
	return _flashLightManager.Add(name, transform,
		color, innerCutoff, outerCutoff, specularColor, attenuationFactors);
}

std::shared_ptr<Material> Resources::CreateMaterial(const std::string& name, glm::vec4 color,
	glm::vec3 reflectCoefficients, float shininess)
{
	return _materialManager.Add(name, color, reflectCoefficients, shininess);
}


#pragma endregion

#pragma region Initialization Methods
void Resources::InitModels()
{
	float triangleWithNormal[18] =
	{
		 .0f,  .6f, .0f,  0, 0, 1,
		-.6f, -.3f, .0f,  0, 0, 1,
		 .6f, -.3f, .0f,  0, 0, 1
	};

	CreateModel("Bushes", bushes, sizeof(bushes) / sizeof(float));
	CreateModel("Gift", gift, sizeof(gift) / sizeof(float));
	CreateModel("Plain", plain, sizeof(plain) / sizeof(float));
	CreateModel("Sphere", sphere, sizeof(sphere) / sizeof(float));
	CreateModel("SuziFlat", suziFlat, sizeof(suziFlat) / sizeof(float));
	CreateModel("SuziSmooth", suziSmooth, sizeof(suziSmooth) / sizeof(float));
	CreateModel("Tree", tree, sizeof(tree) / sizeof(float));
	CreateModel("Triangle", triangleWithNormal, sizeof(triangleWithNormal) / sizeof(float));

	CreateModel("House", "house.obj");
}
void Resources::InitShaders(const std::string& mainCam)
{
	if(_cameraManager.Get(mainCam) == nullptr)
	{
		std::cerr << "Camera "<< mainCam << " must be initialized before shaders!\n";
		return;
	}

	CreateShaderProgram("Test4", mainCam);
	CreateShaderProgram("Constant", mainCam, "Default", "Constant");
	CreateShaderProgram("Lambert", mainCam, "Default", "Lambert");
	CreateShaderProgram("Phong", mainCam, "Default", "Phong");
	CreateShaderProgram("Blinn", mainCam, "Default", "Blinn");
}
void Resources::InitMaterials()
{
	CreateMaterial("Ground", glm::vec4(0.08f, 0.44f, 0.16f, 1.f), glm::vec3(1.f), 8.f);
	CreateMaterial("Tree", glm::vec4(0.33f, 0.65f, 0.13f, 1.f), glm::vec3(1.f), 24.f);
	CreateMaterial("Grass", glm::vec4(0.1f, 0.8f, 0.1f, 1.f), glm::vec3(1.f), 12.f);
	CreateMaterial("BallTest", glm::vec4(0.2f, 0.05f, 0.6f, 1.f), glm::vec3(0.2f, 1.f, 1.f), 80.f);
	CreateMaterial("FlatWhite", glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec3(1.f), 1.f);
}

std::shared_ptr<Camera> Resources::InitMainCamera(const float windowWidth, const float windowHeight, float fov)
{
	return CreateCamera("Main", windowWidth, windowHeight, fov);
}
std::shared_ptr<FlashLight> Resources::InitMainFlashLight()
{
	auto tr = _transformCompositeManager.Add("TransformFlashlight", 
		_transformComponentManager.Add<FollowCamera>("FlashlightFollow", _cameraManager.Get("Main")));
	auto flashLight = CreateFlashLight("MainFlashLight", 
		tr, 
		glm::vec4(1.f, 1.f, 0.8f, 1.f), 
		glm::vec4(1.f, 1.f, .8f, 1.f),
		glm::vec3(1.f, 0.5f, 0.04f),
		glm::cos(glm::radians(15.f)),
		glm::cos(glm::radians(25.f)));
	_cameraManager.Get("Main")->Attach(flashLight);
	return flashLight;
}

void Resources::InitScenes()
{
	InitScene1();
	InitScene2();
	InitScene3();
	InitScene4();
	InitScene5();

	return;
}

void Resources::InitScene1()
{
	auto scene = _sceneManager.Add("Triangle");

	scene->AddObject(std::make_shared<DrawableObject>(_modelManager.Get("Triangle"), _shaderManager.Get("Constant"), nullptr, _materialManager.Get("BallTest")));

	auto light = CreateDirectionalLight("LightAbove", glm::vec4(1.f), glm::vec4(1.f), glm::vec3(0.1f, -1.f, 0.1f));
	scene->AddLight(light);
}
void Resources::InitScene2()
{
	auto scale25 = _transformComponentManager.Add<Scale>("Scale25", glm::vec3(0.25f,0.25f,0.25f));

	_transformCompositeManager.Add("TransformUpBall", scale25)
		->AddTransform(_transformComponentManager.Add<Translate>("MoveUp", glm::vec3(0.f, 2.5f, 0.f)));
	_transformCompositeManager.Add("TransformDownBall", scale25)
		->AddTransform(_transformComponentManager.Add<Translate>("MoveDown", glm::vec3(0.f, -2.5f, 0.f)));
	_transformCompositeManager.Add("TransformRightBall", scale25)
		->AddTransform(_transformComponentManager.Add<Translate>("MoveRight", glm::vec3(2.5f, 0.f, 0.f)));
	_transformCompositeManager.Add("TransformLeftBall", scale25)
		->AddTransform(_transformComponentManager.Add<Translate>("MoveLeft", glm::vec3(-2.5f, 0.f, 0.f)));

	auto scene = _sceneManager.Add("Ballz");
	auto mat = _materialManager.Get("BallTest");

	auto obj = CreateDrawableObject("SphereUp", "Sphere", "Phong", "TransformUpBall");
	obj->SetMaterial(mat);
	scene->AddObject(obj);
	obj = CreateDrawableObject("SphereDown", "Sphere", "Phong", "TransformDownBall");
	obj->SetMaterial(mat);
	scene->AddObject(obj);
	obj = CreateDrawableObject("SphereRight", "Sphere", "Phong", "TransformRightBall");
	obj->SetMaterial(mat);
	scene->AddObject(obj);
	obj = CreateDrawableObject("SphereLeft", "Sphere", "Phong", "TransformLeftBall");
	obj->SetMaterial(mat);
	scene->AddObject(obj);

	
	auto tr = _transformCompositeManager.Add("TransformAtOrigin", _transformComponentManager.Add<Translate>("MoveToOrigin?", glm::vec3(0.f, 0.f, 0.f)));
	auto light = CreatePointLight("LightAtOrigin", tr, glm::vec4(1.f), glm::vec4(1.f), glm::vec3(1.0, 0.07, 0.0002));
	scene->AddLight(light);
}
void Resources::InitScene3()
{
	auto scene = _sceneManager.Add("Forest");

	for(int x = 0; x < 15; x++)
	{
		for(int z = 0; z < 15; z++)
		{
			float xRand = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
			float zRand = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);

			//Resource Manager for transforms wasn't a great idea
			std::string name = std::to_string(x*20+z);
			auto mat = _materialManager.Get("Tree");
			auto model = _modelManager.Get("Tree");
			auto shader = _shaderManager.Get("Blinn");
			auto trans = _transformCompositeManager.Add("TreeTransform" + name, 
				_transformComponentManager.Add<Translate>("MoveTree" + name, glm::vec3(3.f*x + 2.f*xRand, 0.f, 3.f*z + 2.f*zRand)));
			scene->AddObject(CreateDrawableObject("Tree" + name, model, shader, mat, trans));
		}
	}

	for(int x = 0; x < 1200; x++)
	{
		const float xRand = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / 45.f);
		const float zRand = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / 45.f);
		const float scale = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / .6f) + .6f;
		
		std::string name = std::to_string(x);
		auto mat = _materialManager.Get("Grass");
		auto model = _modelManager.Get("Bushes");
		auto shader = _shaderManager.Get("Blinn");
		auto trans = _transformCompositeManager.Add("BushTransform" + name, 
			_transformComponentManager.Add<Translate>("MoveBush" + name, glm::vec3(xRand, 0.f, zRand)));
		trans->AddTransform(_transformComponentManager.Add<Scale>("ScaleBush" + name, glm::vec3(scale, scale, scale)));
		scene->AddObject(CreateDrawableObject("Bush" + name, model, shader, mat, trans));
	}

	scene->AddObject(
		CreateDrawableObject(
			"ForestFloor", 
			"Plain", 
			"Blinn", 
			"Ground",
			_transformCompositeManager.Add(
				"FloorSized", 
				_transformComponentManager.Add<Scale>(
					"Scale1000", 
					glm::vec3(10000.f, 1.f, 10000.f)
	))));


	const auto ffModel = _modelManager.Get("Sphere");
	const auto ffShader = _shaderManager.Get("Constant");
	const auto ffMat = _materialManager.Get("FlatWhite");
	for(int i = 0; i < 16; i++)
	{
		const float xRand = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / 45.f);
		const float zRand = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / 45.f);
		auto tr = _transformCompositeManager.Add("TranformFly" + std::to_string(i), _transformComponentManager.Add<Translate>("MoveFly" + std::to_string(i), glm::vec3(xRand, 0.7, zRand)));
		tr->AddTransform(_transformComponentManager.Add<TranslateRandom>("RandomMoveFly" + std::to_string(i), 80.f));
		tr->AddTransform(_transformComponentManager.Add<Scale>("ScaleFly" + std::to_string(i), glm::vec3(0.01f, 0.01f, 0.01f)));

		auto light = CreatePointLight(
			"LightFly" + std::to_string(i), 
			ffModel, ffShader, tr, 
			glm::vec4(.6f, .6f, 0.f, 1.f), 
			glm::vec4(.1f, .1f, 0.f, 1.f), 
			glm::vec3(2.f, 0.f, 20.f));
		light->SetMaterial(ffMat);
		scene->AddLight(light);
	}

	auto ambLight = CreateAmbientLight("AmbientForestLight", glm::vec4(0.006f, 0.012f, 0.018f, 1.f));
	scene->AddLight(ambLight);

	scene->AddLight(_flashLightManager.Get("MainFlashLight"));
}
void Resources::InitScene4()
{
/*
 (109.08f, 109.08f, 109.08f)
 (0.382f, 0.382f, 0.382f)		(150.f, 0.f, 0.f)
 (0.949f, 0.949f, 0.949f)		(280.f, 0.f, 0.f)
 (1.0f, 1.0f, 1.0f)				(387.f, 0.f, 0.f)
 (0.53f, 0.53f, 0.53f)			(590.f, 0.f, 0.f)
 (11.21f, 11.21f, 11.21f)		(2016.f, 0.f, 0.f)
 (9.45f, 9.45f, 9.45f)			(3712.f, 0.f, 0.f)
 (4.01f, 4.01f, 4.01f)			(7446.f, 0.f, 0.f)
 (3.88f, 3.88f, 3.88f)			(11672.f, 0.f, 0.f)
 
 (22.f, 22.f, 22.f)
 (0.02f, 0.02f, 0.02f)			(15.f, 0.f, 0.f)
 (0.048f, 0.048f, 0.048f)		(28.f, 0.f, 0.f)
 (0.05f, 0.05f, 0.05f)			(38.f, 0.f, 0.f)
 (0.026f, 0.026f, 0.026f)		(59.f, 0.f, 0.f)
 (0.55f, 0.55f, 0.55f)			(201.f, 0.f, 0.f)
 (0.45f, 0.45f, 0.45f)			(371.f, 0.f, 0.f)
 (0.2f, 0.2f, 0.2f)				(744.f, 0.f, 0.f)
 (0.19f, 0.19f, 0.19f)			(1167.f, 0.f, 0.f)
 */
	std::vector<glm::vec3> scales =
	{
		glm::vec3(1.f),
		glm::vec3(0.009f),
		glm::vec3(0.031f),
		glm::vec3(0.032f),
		glm::vec3(0.021f),
		glm::vec3(0.35f),
		glm::vec3(0.25f),
		glm::vec3(0.12f),
		glm::vec3(0.09f),
	};

	std::vector<glm::vec3> dists =
	{
		glm::vec3(30.f, 0.f, 0.f),
		glm::vec3(58.f, 0.f, 0.f),
		glm::vec3(68.f, 0.f, 0.f),
		glm::vec3(79.f, 0.f, 0.f),
		glm::vec3(109.f, 0.f, 0.f),
		glm::vec3(151.f, 0.f, 0.f),
		glm::vec3(214.f, 0.f, 0.f),
		glm::vec3(277.f, 0.f, 0.f)
	};



	auto scene = _sceneManager.Add("SolarSystem");

	auto trans = _transformCompositeManager.Add("SunTransform", 
		_transformComponentManager.Add<Scale>("ScaleSun", scales[0]));
	scene->AddObject(CreateDrawableObject("Sun", "Sphere", "Constant", trans));
	
	trans = _transformCompositeManager.Add("MercuryTransform", 
		_transformComponentManager.Add<Scale>("ScaleMercury", scales[1]));
	trans->AddTransform(_transformComponentManager.Add<Translate>("MoveMercury", dists[0]));
	scene->AddObject(CreateDrawableObject("Mercury", "Sphere", "Blinn", trans));

	trans = _transformCompositeManager.Add("VenusTransform", 
		_transformComponentManager.Add<Scale>("ScaleVenus", scales[2]));
	trans->AddTransform(_transformComponentManager.Add<Translate>("MoveVenus", dists[1]));
	scene->AddObject(CreateDrawableObject("Venus", "Sphere", "Blinn", trans));
	
	trans = _transformCompositeManager.Add("EarthTransform", 
		_transformComponentManager.Add<Scale>("ScaleEarth", scales[3]));
	trans->AddTransform(_transformComponentManager.Add<Translate>("MoveEarth", dists[2]));
	scene->AddObject(CreateDrawableObject("Earth", "Sphere", "Blinn", trans));
	
	trans = _transformCompositeManager.Add("MarsTransform", 
		_transformComponentManager.Add<Scale>("ScaleMars", scales[4]));
	trans->AddTransform(_transformComponentManager.Add<Translate>("MoveMars", dists[3]));
	scene->AddObject(CreateDrawableObject("Mars", "Sphere", "Blinn", trans));
	
	trans = _transformCompositeManager.Add("JupiterTransform", 
		_transformComponentManager.Add<Scale>("ScaleJupiter", scales[5]));
	trans->AddTransform(_transformComponentManager.Add<Translate>("MoveJupiter", dists[4]));
	scene->AddObject(CreateDrawableObject("Jupiter", "Sphere", "Blinn", trans));
	
	trans = _transformCompositeManager.Add("SaturnTransform", 
		_transformComponentManager.Add<Scale>("ScaleSaturn", scales[6]));
	trans->AddTransform(_transformComponentManager.Add<Translate>("MoveSaturn", dists[5]));
	scene->AddObject(CreateDrawableObject("Saturn", "Sphere", "Blinn", trans));
	
	trans = _transformCompositeManager.Add("UranusTransform", 
		_transformComponentManager.Add<Scale>("ScaleUranus", scales[7]));
	trans->AddTransform(_transformComponentManager.Add<Translate>("MoveUranus", dists[6]));
	scene->AddObject(CreateDrawableObject("Uranus", "Sphere", "Blinn", trans));
	
	trans = _transformCompositeManager.Add("NeptuneTransform", 
		_transformComponentManager.Add<Scale>("ScaleNeptune", scales[8]));
	trans->AddTransform(_transformComponentManager.Add<Translate>("MoveNeptune", dists[7]));
	scene->AddObject(CreateDrawableObject("Neptune", "Sphere", "Blinn", trans));


	
	auto tr = _transformCompositeManager.Add("TransformAtOriginSpace", _transformComponentManager.Add<Translate>("MoveToOriginSpace?", glm::vec3(0.f, 0.f, 0.f)));
	auto light = CreatePointLight("LightAtOriginSpace", tr, glm::vec4(1.f, 1.f, 0.f, 1.f), glm::vec4(0.2f, 0.2f, 0.f,1.f), glm::vec3(1.0, 0.07, 0.02));
	scene->AddLight(light);
}
void Resources::InitScene5()
{
	auto scene = _sceneManager.Add("Test");

	scene->AddObject(
		CreateDrawableObject(
			"A Tree", 
			"Tree", 
			"Blinn",
			"BallTest",
			_transformCompositeManager.Add(
				"TheTreesPosition", 
				_transformComponentManager.Add<Translate>(
					"MoveTheTree", 
					glm::vec3(-5.f, 0.f, -5.f)
				))));

	scene->AddObject(
	CreateDrawableObject(
		"ForestHouse", 
		"House", 
		"Blinn", 
		"BallTest",
		_transformCompositeManager.Add(
			"HousePosition", 
			_transformComponentManager.Add<Translate>(
				"MoveHouse", 
				glm::vec3(5.f, 0.f, 5.f)
	))));

	auto dlight = CreateDirectionalLight("LightAboveTest", glm::vec4(1.f), glm::vec4(1.f), glm::vec3(0.2f, 1.f, 0.2f));
	scene->AddLight(dlight);
	auto alight = CreateAmbientLight("AmbientTestLight", glm::vec4(0.2f, 0.2f, 0.2f, 1.f));
	scene->AddLight(alight);
	/*
	auto tr = _transformCompositeManager.Add("TransformAtOrigin", _transformComponentManager.Add<Translate>("MoveToOrigin?", glm::vec3(0.f, 0.f, 0.f)));
	auto plight = CreatePointLight("LightAtOrigin", tr, glm::vec4(1.f), glm::vec4(1.f), glm::vec3(1.0, 0.07, 0.0002));
	scene->AddLight(plight);
	*/
}

#pragma endregion



std::shared_ptr<Scene> Resources::EnableScene(const std::string& name)
{
	auto scene = _sceneManager.Get(name);
	scene->Enable();
	return scene;
}

void Resources::UpdateWindowSize(float width, float height)
{
	for(const auto& [key, value] : _cameraManager.Resources)
		value->UpdateProjection(width, height);
}
void Resources::UpdateCameraFOV(const std::string& name, float fov)
{
	auto camera = _cameraManager.Get(name);
	camera->UpdateFOV(fov);
}
