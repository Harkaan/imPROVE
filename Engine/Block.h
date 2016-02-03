#pragma once

#include "Sprite.h"
#include "TextureCache.h"

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
		Block() { };
		Block(glm::vec3 position, BlockType blocktype);
		~Block();

		void draw();

		Sprite back;
		Sprite front;
		Sprite right;
		Sprite left;
		Sprite up;
		Sprite bottom;

		BlockType blockType;
	};
}

