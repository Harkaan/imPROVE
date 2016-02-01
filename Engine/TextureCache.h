#pragma once

#include <map>
#include <string>
#include "Texture.h"

namespace Engine
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		Texture getTexture(std::string texturePath);

	private:
		std::map<std::string, Texture> _textureMap;
	};
}

