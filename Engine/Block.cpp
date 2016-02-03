#include "Block.h"
#include "Texture.h"
#include "ResourceManager.h"

namespace Engine
{
	Block::Block(glm::vec3 position, BlockType blocktype) :
		blockType(blocktype)
	{
		up.vertices = { 0 + position.x, 0 + position.y, 1 + position.z,   1 + position.x, 1 + position.y, 1 + position.z,   0 + position.x, 1 + position.y, 1 + position.z,
						0 + position.x, 0 + position.y, 1 + position.z,   1 + position.x, 1 + position.y, 1 + position.z,   1 + position.x, 0 + position.y, 1 + position.z };
		up.uv = {0, 0,   1, 1,   0, 1,
				 0, 0,   1, 1,   1, 0};

		bottom.vertices = { 0 + position.x, 0 + position.y, 0 + position.z,   0 + position.x, 1 + position.y, 0 + position.z,   1 + position.x, 0 + position.y, 0 + position.z,
							0 + position.x, 1 + position.y, 0 + position.z,   1 + position.x, 0 + position.y, 0 + position.z,   1 + position.x, 1 + position.y, 0 + position.z };
		bottom.uv = { 0, 0,   1, 0,   0, 1,
					  1, 0,   0, 1,   1, 1 };

		right.vertices = { 1 + position.x, 1 + position.y, 1 + position.z,   1 + position.x, 0 + position.y, 1 + position.z,   1 + position.x, 1 + position.y, 0 + position.z,
						   1 + position.x, 0 + position.y, 1 + position.z,   1 + position.x, 1 + position.y, 0 + position.z,   1 + position.x, 0 + position.y, 0 + position.z };
		right.uv = { 1, 1,   0, 1,   1, 0,
					 0, 1,   1, 0,   0, 0 };

		left.vertices = { 0 + position.x, 0 + position.y, 1 + position.z,   0 + position.x, 0 + position.y, 0 + position.z,   0 + position.x, 1 + position.y, 1 + position.z,
						  0 + position.x, 0 + position.y, 0 + position.z,   0 + position.x, 1 + position.y, 1 + position.z,   0 + position.x, 1 + position.y, 0 + position.z };
		left.uv = { 1, 1,   1, 0,   0, 1,
					1, 0,   0, 1,   0, 0 };

		front.vertices = { 1 + position.x, 1 + position.y, 1 + position.z,   1 + position.x, 1 + position.y, 0 + position.z,   0 + position.x, 1 + position.y, 1 + position.z,
						   1 + position.x, 1 + position.y, 0 + position.z,   0 + position.x, 1 + position.y, 1 + position.z,   0 + position.x, 1 + position.y, 0 + position.z };
		front.uv = { 0, 1,   0, 0,   1, 1,
					 0, 0,   1, 1,   1, 0 };

		back.vertices = { 0 + position.x, 0 + position.y, 0 + position.z,   1 + position.x, 0 + position.y, 0 + position.z,   1 + position.x, 0 + position.y, 1 + position.z,
						  0 + position.x, 0 + position.y, 0 + position.z,   0 + position.x, 0 + position.y, 1 + position.z,   1 + position.x, 0 + position.y, 1 + position.z };
		back.uv = { 0, 0,   0, 1,   1, 1,
					0, 0,   1, 0,   1, 1 };

		if (blockType == BlockType::Stone) {
			GLuint stoneID = ResourceManager::getTexture("Resources/stone.png").id;

			up.textureID = stoneID;
			bottom.textureID = stoneID;
			right.textureID = stoneID;
			left.textureID = stoneID;
			front.textureID = stoneID;
			back.textureID = stoneID;
		}

		if (blockType == BlockType::Grass) {
			GLuint earthID = ResourceManager::getTexture("Resources/earth.png").id;
			GLuint grassID = ResourceManager::getTexture("Resources/grass.png").id;

			up.textureID = grassID;
			bottom.textureID = earthID;
			right.textureID = earthID;
			left.textureID = earthID;
			front.textureID = earthID;
			back.textureID = earthID;
		}
	}

	Block::~Block()
	{
	}

	void Block::draw()
	{
		up.draw();
		bottom.draw();
		right.draw();
		left.draw();
		front.draw();
		back.draw();
	}
}
