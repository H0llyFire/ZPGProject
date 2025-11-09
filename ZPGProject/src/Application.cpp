#include "Application.h"

#include <chrono>
#include <iostream>

#include "gfx/ShaderProgram.h"
#include "gfx/Camera.h"
#include "gfx/lights/FlashLight.h"
#include "gfx/Scene.h"

using timeframe = std::chrono::time_point<std::chrono::high_resolution_clock>;

Application::Application(int width, int height)
	: _width(width), _height(height), _cursorX(0), _cursorY(0)
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
	_ratio = static_cast<float>(width) / static_cast<float>(height);
	glViewport(0, 0, width, height);
}

void Application::Init()
{
	glfwSetWindowUserPointer(_win, this);
	glfwSetErrorCallback(error_callback);
	glfwSetMouseButtonCallback(_win, MouseButtonCallback);
	glfwSetCursorPosCallback(_win, CursorPosCallback);
	glfwSetKeyCallback(_win, KeyPressCallback);
	glfwSetFramebufferSizeCallback(_win, WindowResizeCallback);

	srand(glfwGetTime());

	// get version info
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << '\n';
	std::cout << "Using GLEW: " << glewGetString(GLEW_VERSION) << '\n';
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << '\n';
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << '\n';
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	std::cout << "Using GLFW " << major << '.' << minor << '.' << revision << '\n';

	_textureUnitManager = TextureUnitManager();

	_currentCamera = _resourceManager.InitMainCamera(static_cast<float>(_width), static_cast<float>(_height), 75.f);
	_currentFlashLight = _resourceManager.InitMainFlashLight();
	_resourceManager.InitModels();
	_resourceManager.InitMaterials();
	_resourceManager.InitTextures();
	_resourceManager.InitShaders("Main");
	_resourceManager.InitScenes();

	_currentScene = _resourceManager.EnableScene("Forest");
}

void Application::Run()
{
	glEnable(GL_DEPTH_TEST);

	timeframe lastFrame = std::chrono::high_resolution_clock::now();
	while (!glfwWindowShouldClose(_win))
	{
	    timeframe currentFrame = std::chrono::high_resolution_clock::now();
	    std::chrono::duration<float> elapsed = (currentFrame - lastFrame);
		const float dTime = elapsed.count();
	    lastFrame = currentFrame;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(_keyIsPressed[GLFW_KEY_W])
			_currentCamera->MoveForward(dTime * (_keyIsPressed[GLFW_KEY_LEFT_SHIFT] ? 4.f : 1.f));
		if(_keyIsPressed[GLFW_KEY_S])
			_currentCamera->MoveBackward(dTime * (_keyIsPressed[GLFW_KEY_LEFT_SHIFT] ? 4.f : 1.f));
		if(_keyIsPressed[GLFW_KEY_A])
			_currentCamera->MoveLeft(dTime * (_keyIsPressed[GLFW_KEY_LEFT_SHIFT] ? 4.f : 1.f));
		if(_keyIsPressed[GLFW_KEY_D])
			_currentCamera->MoveRight(dTime * (_keyIsPressed[GLFW_KEY_LEFT_SHIFT] ? 4.f : 1.f));
		if(_keyIsPressed[GLFW_KEY_UP])
			_currentCamera->UpdateFOV(5.0f * dTime);
		if(_keyIsPressed[GLFW_KEY_DOWN])
			_currentCamera->UpdateFOV(-5.0f * dTime);


		if(_currentScene)
			_currentScene->Draw(dTime, std::make_shared<TextureUnitManager>(_textureUnitManager));

		
		glfwPollEvents();
		glfwSwapBuffers(_win);
	}
	glfwDestroyWindow(_win);

	glfwTerminate();
}

void Application::error_callback(int error, const char* description)
{
	std::cerr << description;
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
	if (!app) 
		return;
	
	//TODO: Make non-repeating key presses eat the pressed bool and process them outside a static function
	if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if(action == GLFW_PRESS)
	{
		app->_keyIsPressed[key] = true;

		if(key == GLFW_KEY_F && app->_currentFlashLight)
			app->_currentFlashLight->Toggle();
		else if(key == GLFW_KEY_F1)
			app->_currentScene = app->_resourceManager.EnableScene("Triangle");
		else if(key == GLFW_KEY_F2)
			app->_currentScene = app->_resourceManager.EnableScene("Ballz");
		else if(key == GLFW_KEY_F3)
			app->_currentScene = app->_resourceManager.EnableScene("Forest");
		else if(key == GLFW_KEY_F4)
			app->_currentScene = app->_resourceManager.EnableScene("SolarSystem");
		else if(key == GLFW_KEY_F5)
			app->_currentScene = app->_resourceManager.EnableScene("Test");
	}
	else if(action == GLFW_RELEASE)
		app->_keyIsPressed[key] = false;
}
void Application::WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (!app) 
		return;

	app->_width = width;
	app->_height = height;
	app->_resourceManager.UpdateWindowSize(static_cast<float>(width), static_cast<float>(height));
}
