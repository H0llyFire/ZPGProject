#pragma once
#include <string>
#include <GL/glew.h>

#include "stb_image.h"

class Texture
{
private:
	std::string _filePath;
	int _width, _height, _channels;
public:
	GLuint Id;
	Texture(const std::string& filePath);

	void Bind(int slot);
	void Unbind();
};
