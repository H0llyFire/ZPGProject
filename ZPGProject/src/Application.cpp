#include "Application.h"

#include <chrono>
#include <iostream>

#include "gfx/models/bushes.h"
#include "gfx/models/gift.h"
#include "gfx/models/plain.h"
#include "gfx/models/sphere.h"
#include "gfx/models/suzi_flat.h"
#include "gfx/models/suzi_smooth.h"
#include "gfx/models/tree.h"

#include "gfx/trans/Rotate.h"
#include "gfx/trans/RotateTime.h"
#include "gfx/trans/Scale.h"
#include "gfx/trans/Translate.h"

using timeframe = std::chrono::time_point<std::chrono::steady_clock>;

Application::Application(int width, int height)
	: _width(width), _height(height)
{
	if (!glfwInit()) 
	{
	   std::cout << "ERROR: could not start GLFW3\n";
	   exit(EXIT_FAILURE);
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);

	
	_win = glfwCreateWindow(width, height, "ZPG", nullptr, nullptr);
	if (!_win)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(_win);
	glfwSwapInterval(1);

	
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
	
	glfwGetFramebufferSize(_win, &width, &height);
	_ratio = width / static_cast<float>(height);
	glViewport(0, 0, width, height);
}

void Application::Init()
{
	glfwSetWindowUserPointer(_win, this);
	glfwSetErrorCallback(error_callback);
	glfwSetMouseButtonCallback(_win, MouseButtonCallback);
	glfwSetCursorPosCallback(_win, CursorPosCallback);
	glfwSetKeyCallback(_win, KeyPressCallback);
	// get version info
	
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << '\n';
	std::cout << "Using GLEW: " << glewGetString(GLEW_VERSION) << '\n';
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << '\n';
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << '\n';
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	std::cout << "Using GLFW " << major << '.' << minor << '.' << revision << '\n';
}

void Application::Run()
{
	
	float triangleWithNormal[18] =
	{
		 .0f,  .6f, .0f,  0, 0, 1,
		-.6f, -.3f, .0f,  0, 0, 1,
		 .6f, -.3f, .0f,  0, 0, 1
	};

	Camera camera{static_cast<float>(_width), static_cast<float>(_height)};
	_currentCamera = &camera;

	Shader shaderTest1(&camera, "Test1");
	Shader shaderTest2(&camera,"Test2");
	Shader shaderTest3(&camera,"Test3");
	Shader shaderTest4(&camera,"Test4", "Test3");
	Shader shaderTest5(&camera,"Test4");


	Model modelBushes(bushes, sizeof(bushes) / sizeof(float));
	Model modelGift(gift, sizeof(gift) / sizeof(float));
	Model modelPlain(plain, sizeof(plain) / sizeof(float));
	Model modelSphere(sphere, sizeof(sphere) / sizeof(float));
	Model modelSuziFlat(suziFlat, sizeof(suziFlat) / sizeof(float));
	Model modelSuziSmooth(suziSmooth, sizeof(suziSmooth) / sizeof(float));
	Model modelTree(tree, sizeof(tree) / sizeof(float));

	Model modelTriangle(triangleWithNormal, sizeof(triangleWithNormal) / sizeof(float));

	
	std::shared_ptr<RotateTime> timedRotationX = std::make_shared<RotateTime>(glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	std::shared_ptr<RotateTime> timedRotationY = std::make_shared<RotateTime>(glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	std::shared_ptr<RotateTime> timedRotationZ = std::make_shared<RotateTime>(glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	std::shared_ptr<Translate> translUpLeft = std::make_shared<Translate>(glm::vec3(-0.5f, 0.5f, 0.0f));
	std::shared_ptr<Translate> translUpRight = std::make_shared<Translate>(glm::vec3(0.5f, 0.5f, 0.0f));
	std::shared_ptr<Translate> translDownLeft = std::make_shared<Translate>(glm::vec3(-0.5f, -0.5f, 0.0f));
	std::shared_ptr<Translate> translDownRight = std::make_shared<Translate>(glm::vec3(0.5f, -0.5f, 0.0f));
	
	std::shared_ptr<Scale> scale5 = std::make_shared<Scale>(glm::vec3(0.05f, 0.05f, 0.05f));
	std::shared_ptr<Scale> scale10 = std::make_shared<Scale>(glm::vec3(0.1f, 0.1f, 0.1f));
	std::shared_ptr<Scale> scale15 = std::make_shared<Scale>(glm::vec3(0.15f, 0.15f, 0.15f));
	std::shared_ptr<Scale> scale25 = std::make_shared<Scale>(glm::vec3(0.25f, 0.25f, 0.25f));
	std::shared_ptr<Scale> scale50 = std::make_shared<Scale>(glm::vec3(0.5f, 0.5f, 0.5f));

	Transforms None{};

	Transforms RotatingTransf(timedRotationZ);

	Transforms TransfUpLeft(translUpLeft);
	TransfUpLeft.AddTransform(scale25);
	Transforms TransfUpRight(translUpRight);
	TransfUpRight.AddTransform(scale25);
	Transforms TransfDownLeft(translDownLeft);
	TransfDownLeft.AddTransform(scale25);
	Transforms TransfDownRight(translDownRight);
	TransfDownRight.AddTransform(scale25);
	
	Transforms size5(scale5);
	Transforms size10(scale10);
	Transforms size25(scale25);
	Transforms size50(scale50);





	DrawableObject objTriangle(&modelTriangle, &shaderTest4, &RotatingTransf);

	DrawableObject objSphere1(&modelSphere, &shaderTest4, &TransfUpLeft);
	DrawableObject objSphere2(&modelSphere, &shaderTest5, &TransfUpRight);
	DrawableObject objSphere3(&modelSphere, &shaderTest5, &TransfDownLeft);
	DrawableObject objSphere4(&modelSphere, &shaderTest4, &TransfDownRight);

	DrawableObject objSuziFlat(&modelSuziFlat, &shaderTest4, &size50);
	DrawableObject objSuziSmooth(&modelSuziSmooth, &shaderTest4, &size50);
	DrawableObject objTree(&modelTree, &shaderTest4, &size25);
	DrawableObject objBushes(&modelBushes, &shaderTest4, &size50);
	DrawableObject objGift(&modelGift, &shaderTest4, &RotatingTransf);
	DrawableObject objPlain(&modelPlain, &shaderTest4, &size50);

	Scene test1{};
	test1.AddObject(objTriangle);

	Scene test2{};
	test2.AddObject(objSphere1);
	test2.AddObject(objSphere2);
	test2.AddObject(objSphere3);
	test2.AddObject(objSphere4);

	Scene test3{};

	std::vector<std::shared_ptr<Translate>> translates;
	std::vector<std::shared_ptr<Transforms>> transforms;
	for(int i = 0; i < 8; i++)
	{
		transforms.push_back(std::make_shared<Transforms>());
		translates.push_back(std::make_shared<Translate>(glm::vec3(-0.9f + i * 0.25f, -0.6f, 0.0f)));

		transforms[i]->AddTransform(translates[i]);
		transforms[i]->AddTransform(scale10);
		test3.AddObject(DrawableObject(&modelTree, &shaderTest5, transforms[i].get()));
	}

	for(int i = 0; i < 10; i++)
	{
		transforms.push_back(std::make_shared<Transforms>());
		translates.push_back(std::make_shared<Translate>(glm::vec3(-0.9f + (i % 10) * 0.2f,  0.2f, 0.0f)));
		transforms[8 + i]->AddTransform(translates[8 + i]);
		transforms[8 + i]->AddTransform(scale10);
		transforms[8 + i]->AddTransform(timedRotationY);
		test3.AddObject(DrawableObject(&modelSuziFlat, &shaderTest5, transforms[8 + i].get()));
	}
	srand(static_cast<unsigned>(time(0)));
	for(int i = 0; i < 10; i++)
	{
		float x = -1.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(2.f)));
		float y = -1.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(2.f)));
		transforms.push_back(std::make_shared<Transforms>());
		translates.push_back(std::make_shared<Translate>(glm::vec3(x, y, -1.0f)));
		transforms[18 + i]->AddTransform(translates[18 + i]);
		transforms[18 + i]->AddTransform(scale15);
		test3.AddObject(DrawableObject(&modelSphere, &shaderTest4, transforms[18 + i].get()));
	}

	Scene test4{};

	for(int x = 0; x < 25; x++)
	{
		for(int z = 0; z < 25; z++)
		{
			transforms.push_back(std::make_shared<Transforms>());
			translates.push_back(std::make_shared<Translate>(glm::vec3(1*x, -0.5f, 1*z)));
			transforms.back()->AddTransform(translates.back());
			test4.AddObject(DrawableObject(&modelTree, &shaderTest5, transforms.back().get()));
		}
	}





	glEnable(GL_DEPTH_TEST);

	timeframe lastFrame = std::chrono::high_resolution_clock::now();
	while (!glfwWindowShouldClose(_win))
	{
	    timeframe currentFrame = std::chrono::high_resolution_clock::now();
	    std::chrono::duration<float> elapsed = currentFrame - lastFrame;
		float dTime = elapsed.count();
	    lastFrame = currentFrame;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(_keyIsPressed[GLFW_KEY_W])
			_currentCamera->MoveForward(dTime);
		if(_keyIsPressed[GLFW_KEY_S])
			_currentCamera->MoveBackward(dTime);
		if(_keyIsPressed[GLFW_KEY_A])
			_currentCamera->MoveLeft(dTime);
		if(_keyIsPressed[GLFW_KEY_D])
			_currentCamera->MoveRight(dTime);






		test4.Draw(dTime);
		
		glfwPollEvents();
		glfwSwapBuffers(_win);
	}
	glfwDestroyWindow(_win);

	glfwTerminate();
}

void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Application::CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (!app || !app->_rightMousePressed) 
		return;
	
    float sensitivity = 0.01f;

    float yaw = sensitivity * (xpos - app->_cursorX);
    float pitch = sensitivity * (ypos - app->_cursorY);

	app->_cursorX = xpos;
	app->_cursorY = ypos;


	app->_currentCamera->CalcTarget(yaw, pitch);
}

void Application::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (!app) 
		return;
	
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            app->_rightMousePressed = true;
            glfwGetCursorPos(window, &app->_cursorX, &app->_cursorY);
        } else if (action == GLFW_RELEASE) {
            app->_rightMousePressed = false;
        }
    }
}

void Application::KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action != GLFW_PRESS && action != GLFW_REPEAT && action != GLFW_RELEASE)
		return;
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if(action == GLFW_PRESS)
		app->_keyIsPressed[key] = true;
	else if(action == GLFW_RELEASE)
		app->_keyIsPressed[key] = false;
}
