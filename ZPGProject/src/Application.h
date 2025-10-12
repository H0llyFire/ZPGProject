#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Application
{
private:
	GLFWwindow* _win;
	int _width, _height;
	float _ratio;
public:
	Application(int width = 1600, int height = 900);
	void Init();
	void Run();

	static void error_callback(int error, const char* description);
};