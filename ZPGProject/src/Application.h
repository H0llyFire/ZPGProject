#pragma once
#include <unordered_map>

// ReSharper disable once CppUnusedIncludeDirective
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Resources.h"
#include "gfx/TextureUnitManager.h"

class Camera;

class Application
{
private:
	GLFWwindow* _win;
	int _width, _height;
	float _ratio;

	std::shared_ptr<Camera> _currentCamera;
	std::shared_ptr<FlashLight> _currentFlashLight;
	std::shared_ptr<Scene> _currentScene;
	Resources _resourceManager;
	TextureUnitManager _textureUnitManager;

	std::unordered_map<int, bool> _keyIsPressed;
	bool _rightMousePressed = false;
	double _cursorX, _cursorY;

	static void error_callback(int error, const char* description);
	static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void WindowResizeCallback(GLFWwindow* window, int width, int height);
public:
	Application(int width = 1600, int height = 900);
	void Init();
	void Run();
};
