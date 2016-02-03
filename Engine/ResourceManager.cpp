#include "ResourceManager.h"

namespace Engine
{
	TextureCache ResourceManager::_textureCache;

	Texture ResourceManager::getTexture(std::string texturePath)
	{
		return _textureCache.getTexture(texturePath);
	}
}