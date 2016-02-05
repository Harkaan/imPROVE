#pragma once

#include "Sprite.h"
#include <glm\glm.hpp>

namespace Engine
{
	enum class BlockType
	{
		Stone,
		Grass,
		Water
	};

	class Block
	{
	public:
		Block() {};
		Block(glm::vec3 position, BlockType blocktype);
		~Block();

		Sprite * back;
		Sprite * front;
		Sprite * right;
		Sprite * left;
		Sprite * up;
		Sprite * bottom;

		BlockType blockType;
		ColorRGBA color;
	};
}

