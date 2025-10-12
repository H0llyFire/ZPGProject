#pragma once
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ResourceManager.h"
#include "gfx/Camera.h"
#include "gfx/DrawableObject.h"
#include "gfx/Model.h"
#include "gfx/Scene.h"
#include "gfx/Shader.h"

class Application
{
private:
	GLFWwindow* _win;
	int _width, _height;
	float _ratio;

	ResourceManager<Shader> _shaderManager;
	ResourceManager<Transform> _transformManager;
	ResourceManager<Transforms> _transformGroupManager;
	ResourceManager<Model> _modelManager;
	ResourceManager<DrawableObject> _objectManager;
	ResourceManager<Scene> _sceneManager;
	ResourceManager<Camera> _cameraManager;

	Camera* _currentCamera;

	std::unordered_map<int, bool> _keyIsPressed;

	static void error_callback(int error, const char* description);
	static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


	bool _rightMousePressed = false;
	double _cursorX, _cursorY;
public:
	Application(int width = 1600, int height = 900);
	void Init();
	void Run();

};
