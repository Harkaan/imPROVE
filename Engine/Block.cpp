#include "Block.h"
#include "ResourceManager.h"
#include "Chunk.h"
#include <iostream>

const std::string TEXTURE_PATH_STONE = "Resources/grey.png";
const std::string TEXTURE_PATH_GRASS = "Resources/green.png";
const std::string TEXTURE_PATH_WATER = "Resources/blue.png";
const std::string TEXTURE_PATH_DIRT = "Resources/brown.png";
const std::string TEXTURE_PATH_LEAF = "Resources/green2.png";
const std::string TEXTURE_PATH_WOOD = "Resources/brown2.png";

namespace Engine
{
	Block::Block(glm::vec3 position, bool spritesLoaded[6], BlockType blocktype) :
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
			otherID = Engine::ResourceManager::getTexture(TEXTURE_PATH_DIRT).id;
		}
		else if (blockType == BlockType::Water) {
			upID = Engine::ResourceManager::getTexture(TEXTURE_PATH_WATER).id;
			otherID = upID;
		}
		else if (blockType == BlockType::Leaf) {
			upID = Engine::ResourceManager::getTexture(TEXTURE_PATH_LEAF).id;
			otherID = upID;
		}
		else if (blockType == BlockType::Wood) {
			upID = Engine::ResourceManager::getTexture(TEXTURE_PATH_WOOD).id;
			otherID = upID;
		}
		
		if (spritesLoaded[0]) {
			Sprite *bottom = new Sprite({ glm::vec3(0 + position.x, 0 + position.y, 0 + position.z),
								  glm::vec3(1 + position.x, 0 + position.y, 0 + position.z),
								  glm::vec3(0 + position.x, 1 + position.y, 0 + position.z),
								  glm::vec3(1 + position.x, 1 + position.y, 0 + position.z) },
								  color, { 0, 0, 1, 1 }, otherID);
			sprites.push_back(bottom);
		}
		if (spritesLoaded[1]) {
			Sprite *up = new Sprite({ glm::vec3(0 + position.x, 0 + position.y, 1 + position.z),
									  glm::vec3(1 + position.x, 0 + position.y, 1 + position.z),
									  glm::vec3(0 + position.x, 1 + position.y, 1 + position.z),
									  glm::vec3(1 + position.x, 1 + position.y, 1 + position.z) },
									  color, { 0, 0, 1, 1 }, upID);
			sprites.push_back(up);
		}
		if (spritesLoaded[2]) {
			Sprite *back = new Sprite({ glm::vec3(0 + position.x, 0 + position.y, 0 + position.z),
										glm::vec3(1 + position.x, 0 + position.y, 0 + position.z),
										glm::vec3(0 + position.x, 0 + position.y, 1 + position.z),
										glm::vec3(1 + position.x, 0 + position.y, 1 + position.z) },
										color, { 0, 0, 1, 1 }, otherID);
			sprites.push_back(back);
		}
		if (spritesLoaded[3]) {
			Sprite *front = new Sprite({ glm::vec3(0 + position.x, 1 + position.y, 0 + position.z),
										 glm::vec3(1 + position.x, 1 + position.y, 0 + position.z),
										 glm::vec3(0 + position.x, 1 + position.y, 1 + position.z),
										 glm::vec3(1 + position.x, 1 + position.y, 1 + position.z) },
										 color, { 0, 0, 1, 1 }, otherID);
			sprites.push_back(front);
		}
		if (spritesLoaded[4]) {
			Sprite *left = new Sprite({ glm::vec3(0 + position.x, 0 + position.y, 0 + position.z),
										glm::vec3(0 + position.x, 1 + position.y, 0 + position.z),
										glm::vec3(0 + position.x, 0 + position.y, 1 + position.z),
										glm::vec3(0 + position.x, 1 + position.y, 1 + position.z) },
										color, { 0, 0, 1, 1 }, otherID);
			sprites.push_back(left);
		}
		if (spritesLoaded[5]) {
			Sprite *right = new Sprite({ glm::vec3(1 + position.x, 0 + position.y, 0 + position.z),
										 glm::vec3(1 + position.x, 1 + position.y, 0 + position.z),
										 glm::vec3(1 + position.x, 0 + position.y, 1 + position.z),
										 glm::vec3(1 + position.x, 1 + position.y, 1 + position.z) },
										 color, { 0, 0, 1, 1 }, otherID);
			sprites.push_back(right);
		}
	}

	Block::~Block()
	{
		for (int i = 0; i < sprites.size(); i++){
			delete (sprites[i]);
		}
	}
}
