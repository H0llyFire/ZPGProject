#include "TextureUnitManager.h"

#include "Texture.h"

TextureUnitManager::TextureUnitManager(int maxUnits)
{
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &_maxUnits);
    if(maxUnits > 0 && maxUnits < _maxUnits)
		_maxUnits = maxUnits;
	_boundTextureIds.resize(_maxUnits, 0);
}

int TextureUnitManager::Bind(const std::shared_ptr<Texture>& texture)
{
	for(int i = 0; i < _maxUnits; i++)
	{
		if(_boundTextureIds[i] == texture->Id)
			return i;
	}
	const int unit = _currentUnit++;
	texture->Bind(unit);
	_boundTextureIds[unit] = texture->Id;
	_currentUnit = _currentUnit % _maxUnits;
	return unit;
}

void TextureUnitManager::UnbindAll()
{
	for (int i = 0; i < _maxUnits; i++)
		{
		if (_boundTextureIds[i] != 0)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
			_boundTextureIds[i] = 0;
		}
	}
}
