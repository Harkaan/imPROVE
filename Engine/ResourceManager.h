#pragma once

#include "TextureCache.h"
#include <string>

namespace Engine
{
	class ResourceManager
	{
	public:
		static Texture getTexture(std::string texturePath);

	private:
		static TextureCache _textureCache;
	};
}

