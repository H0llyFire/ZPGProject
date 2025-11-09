#pragma once
#include <memory>
#include <vector>
#include <GL/glew.h>

class Texture;

class TextureUnitManager
{
	int _maxUnits;
	int _currentUnit = 0;
	std::vector<int> _boundTextureIds;
public:
	TextureUnitManager(int maxUnits = 0);
	int Bind(const std::shared_ptr<Texture>& texture);
	void UnbindAll();
};
