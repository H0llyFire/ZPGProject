#include "FragmentShader.h"

#include <fstream>
#include <iostream>
#include <sstream>

FragmentShader::FragmentShader(const std::string& shaderName)
{
    std::ifstream shaderFile;
    std::string shaderStr;
    try 
    {
        std::stringstream shaderStream;

        shaderFile.open(_shaderPath + shaderName + ".frag");
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();

        shaderStr = shaderStream.str();
    }
    catch(std::ifstream::failure &e)
    {
        std::cout << "Fragment Shader Reading Error\n";
    }

    const char* shader = shaderStr.c_str();


	_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_shader, 1, &shader, nullptr);
	glCompileShader(_shader);
}
