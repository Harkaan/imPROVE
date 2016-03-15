#pragma once

#include "Sprite.h"
#include <vector>
#include <glm\glm.hpp>

namespace Engine
{
	enum class BlockType
	{
		Void,
		Stone,
		Grass,
		Water,
		Leaf,
		Wood,
		Source
	};

	class Block
	{
	public:
		Block() {};
		Block(glm::vec3 position, bool spritesLoaded[6], BlockType blocktype);
		~Block();

		std::vector<Sprite*> sprites;

		BlockType blockType;
		ColorRGBA color;
	};
}

