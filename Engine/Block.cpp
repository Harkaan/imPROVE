#include "Block.h"
#include "ResourceManager.h"
#include "Chunk.h"

const std::string TEXTURE_PATH_STONE = "Resources/stone.png";
const std::string TEXTURE_PATH_GRASS = "Resources/grass.png";
const std::string TEXTURE_PATH_WATER = "Resources/water.png";
const std::string TEXTURE_PATH_EARTH = "Resources/earth.png";
const std::string TEXTURE_PATH_WOOD = "Resources/wood.png";
const std::string TEXTURE_PATH_LEAVES = "Resources/leaves.png";

namespace Engine
{
	Block::Block(glm::vec3 position, BlockType blocktype) :
		blockType(blocktype)
	{
		static int upID;
		static int otherID;

		if (blockType == BlockType::Stone) {
			upID = Engine::ResourceManager::getTexture(TEXTURE_PATH_STONE).id;
			otherID = upID;
		}
		else if (blockType == BlockType::Grass) {
			upID = Engine::ResourceManager::getTexture(TEXTURE_PATH_GRASS).id;
			otherID = Engine::ResourceManager::getTexture(TEXTURE_PATH_EARTH).id;
		}
		else if (blockType == BlockType::Water) {
			upID = Engine::ResourceManager::getTexture(TEXTURE_PATH_WATER).id;
			otherID = upID;
		}
		else if (blockType == BlockType::Wood) {
			upID = Engine::ResourceManager::getTexture(TEXTURE_PATH_WOOD).id;
			otherID = upID;
		}
		else if (blockType == BlockType::Leaves) {
			upID = Engine::ResourceManager::getTexture(TEXTURE_PATH_LEAVES).id;
			otherID = upID;
		}

		bottom = new Sprite({	glm::vec3(0 + position.x, 0 + position.y, 0 + position.z),
								glm::vec3(1 + position.x, 0 + position.y, 0 + position.z),
								glm::vec3(0 + position.x, 1 + position.y, 0 + position.z),
								glm::vec3(1 + position.x, 1 + position.y, 0 + position.z) },
								color, { 0, 0, 1, 1 }, otherID);
		up = new Sprite({		glm::vec3(0 + position.x, 0 + position.y, 1 + position.z),
								glm::vec3(1 + position.x, 0 + position.y, 1 + position.z),
								glm::vec3(0 + position.x, 1 + position.y, 1 + position.z),
								glm::vec3(1 + position.x, 1 + position.y, 1 + position.z) }, 
								color, { 0, 0, 1, 1 }, upID);
		back = new Sprite({		glm::vec3(0 + position.x, 0 + position.y, 0 + position.z),
								glm::vec3(1 + position.x, 0 + position.y, 0 + position.z),
								glm::vec3(0 + position.x, 0 + position.y, 1 + position.z),
								glm::vec3(1 + position.x, 0 + position.y, 1 + position.z) },
								color, { 0, 0, 1, 1 }, otherID);
		front = new Sprite({	glm::vec3(0 + position.x, 1 + position.y, 0 + position.z),
								glm::vec3(1 + position.x, 1 + position.y, 0 + position.z),
								glm::vec3(0 + position.x, 1 + position.y, 1 + position.z),
								glm::vec3(1 + position.x, 1 + position.y, 1 + position.z) },
								color, { 0, 0, 1, 1 }, otherID);
		left = new Sprite({		glm::vec3(0 + position.x, 0 + position.y, 0 + position.z),
								glm::vec3(0 + position.x, 1 + position.y, 0 + position.z),
								glm::vec3(0 + position.x, 0 + position.y, 1 + position.z),
								glm::vec3(0 + position.x, 1 + position.y, 1 + position.z) },
								color, { 0, 0, 1, 1 }, otherID);
		right = new Sprite({	glm::vec3(1 + position.x, 0 + position.y, 0 + position.z),
								glm::vec3(1 + position.x, 1 + position.y, 0 + position.z),
								glm::vec3(1 + position.x, 0 + position.y, 1 + position.z),
								glm::vec3(1 + position.x, 1 + position.y, 1 + position.z) },
								color, { 0, 0, 1, 1 }, otherID);
	}

	Block::~Block()
	{
	}
}
