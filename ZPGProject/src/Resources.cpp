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

#include "gfx/gfxHelpers/FragmentShader.h"
#include "gfx/gfxHelpers/VertexShader.h"

#include "gfx/Camera.h"
#include "gfx/DrawableObject.h"
#include "gfx/Light.h"
#include "gfx/Model.h"
#include "gfx/Scene.h"
#include "gfx/ShaderProgram.h"

std::shared_ptr<VertexShader> Resources::CreateVertexShader(const std::string& name)
{
	return _vertexShaderManager.Add(name, name);
}

std::shared_ptr<FragmentShader> Resources::CreateFragmentShader(const std::string& name)
{
	return _fragmentShaderManager.Add(name, name);
}

std::shared_ptr<ShaderProgram> Resources::CreateShaderProgram(const std::string& name, const std::string& cameraName, const std::string& vertexShaderName, const std::string& fragmentShaderName)
{
	auto sp = _shaderManager.Add(name, _cameraManager.Get(cameraName), _vertexShaderManager.Get(vertexShaderName), _fragmentShaderManager.Get(fragmentShaderName));
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

std::shared_ptr<Camera> Resources::CreateCamera(const std::string& name, float width, float height, float fov)
{
	return _cameraManager.Add(name, width, height, fov);
}

std::shared_ptr<Light> Resources::CreateLight(const std::string& name, std::shared_ptr<TransformComposite>& transform, glm::vec4 color, glm::vec4 specularColor)
{
	return _lightManager.Add(name, transform, color, specularColor);
}

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
}

//Camera Main MUST EXIST BEFORE (because why not, I have free will)
void Resources::InitShaders(const std::string& mainCam)
{
	if(_cameraManager.Get(mainCam) == nullptr)
	{
		std::cerr << "Camera "<< mainCam << " must be initialized before shaders!\n";
		return;
	}

	CreateShaderProgram("Test4", mainCam);
	CreateShaderProgram("Constant", mainCam);
	CreateShaderProgram("Lambert", mainCam);
	CreateShaderProgram("Phong", mainCam);
	CreateShaderProgram("Blinn", mainCam);
}

std::shared_ptr<Camera> Resources::InitCamera(const float windowWidth, const float windowHeight, float fov)
{
	return CreateCamera("Main", windowWidth, windowHeight, fov);
}

void Resources::InitScenes()
{
	//InitScene1();
	InitScene2();
	//InitScene3();
	//InitScene4();
}

void Resources::InitScene1()
{
	auto scene = _sceneManager.Add("Triangle");

	scene->AddObject(std::make_shared<DrawableObject>(_modelManager.Get("Triangle"), _shaderManager.Get("Blinn"), nullptr));

	auto tr = _transformCompositeManager.Add("TransformAbove", _transformComponentManager.Add<Translate>("MoveAbove", glm::vec3(1.f, 0.f, 1.f)));
	auto light = CreateLight("LightAbove", tr, glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f));
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
	scene->AddObject(CreateDrawableObject("SphereUp", "Sphere", "Phong", "TransformUpBall"));
	scene->AddObject(CreateDrawableObject("SphereDown", "Sphere", "Phong", "TransformDownBall"));
	scene->AddObject(CreateDrawableObject("SphereRight", "Sphere", "Phong", "TransformRightBall"));
	scene->AddObject(CreateDrawableObject("SphereLeft", "Sphere", "Phong", "TransformLeftBall"));

	
	auto tr = _transformCompositeManager.Add("TransformAtOrigin", _transformComponentManager.Add<Translate>("MoveToOrigin?", glm::vec3(0.f, 0.f, 0.f)));
	auto light = CreateLight("LightOrigin", tr, glm::vec4(0.8f, 0.4f, 0.3f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f));
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
			auto trans = _transformCompositeManager.Add("TreeTransform" + name, 
				_transformComponentManager.Add<Translate>("MoveTree" + name, glm::vec3(3.f*x + 2.f*xRand, 0.f, 3.f*z + 2.f*zRand)));
			scene->AddObject(CreateDrawableObject("Tree" + name, "Tree", "Blinn", trans));
		}
	}

	for(int x = 0; x < 1200; x++)
	{
		float xRand = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / 45.f);
		float zRand = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / 45.f);

		float scale = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / .6f) + .6f;
		
		std::string name = std::to_string(x);
		auto trans = _transformCompositeManager.Add("BushTransform" + name, 
			_transformComponentManager.Add<Translate>("MoveBush" + name, glm::vec3(xRand, 0.f, zRand)));
		trans->AddTransform(_transformComponentManager.Add<Scale>("ScaleBush" + name, glm::vec3(scale, scale, scale)));
		scene->AddObject(CreateDrawableObject("Bush" + name, "Bushes", "Blinn", trans));
	}

	scene->AddObject(CreateDrawableObject("ForestFloor", "Plain", "Blinn", 
		_transformCompositeManager.Add("FloorSized", _transformComponentManager.Add<Scale>("Scale1000", glm::vec3(10000.f, 1.f, 10000.f)))
		));
	/*
	auto tr = _transformCompositeManager.Add("TransformHighUp", _transformComponentManager.Add<Translate>("MoveHighUp", glm::vec3(0.f, 1.f, 0.f)));
	auto light = CreateLight("LightHigh", tr, glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f));
	scene->AddLight(light);
	*/

	for(int i = 0; i < 16; i++)
	{
		float xRand = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / 45.f);
		float zRand = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / 45.f);
		auto tr = _transformCompositeManager.Add("TranformFly" + std::to_string(i), _transformComponentManager.Add<Translate>("MoveFly" + std::to_string(i), glm::vec3(xRand, 0.3, zRand)));
		tr->AddTransform(_transformComponentManager.Add<TranslateRandom>("RandomMoveFly" + std::to_string(i), 0.8f));

		auto light = CreateLight("LightFly" + std::to_string(i), tr, glm::vec4(1.f, 1.f, 0.f, 1.f), glm::vec4(.6f, .6f, .6f, 1.f));
		scene->AddLight(light);
	}
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
	auto light = CreateLight("LightOriginSpace", tr, glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f));
	scene->AddLight(light);
}

std::shared_ptr<Scene> Resources::EnableScene(const std::string& name)
{
	auto scene = _sceneManager.Get(name);

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
