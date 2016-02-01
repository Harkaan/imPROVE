#include "TextureCache.h"
#include <iostream>

namespace Engine
{
	TextureCache::TextureCache()
	{
	}

	TextureCache::~TextureCache()
	{
	}

	Texture TextureCache::getTexture(std::string texturePath)
	{
		//Cherche la texture dans le cache
		auto mit = _textureMap.find(texturePath);

		//Si la texture recherchée n'est pas dans le cache, on la charge
		if (mit == _textureMap.end()) {
			Texture newTexture = Texture::loadPNG(texturePath); // on charge la texture
			std::cout << "Loaded new texture " << texturePath << std::endl;
			_textureMap.insert(make_pair(texturePath, newTexture)); // on l'insère dans la map (cache)
			return newTexture;
		}

		//Si la texture existe on la renvoie
		return mit->second;
	}
}
