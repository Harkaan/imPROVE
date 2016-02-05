#include "Rock.h"
#include <vector>
#include <Engine\Block.h>


Rock::Rock(glm::vec3 position) : Structure(position)
{
	_blockMap.push_back(std::make_pair(glm::vec3(0, 0, 0), Engine::BlockType::Stone));
	_blockMap.push_back(std::make_pair(glm::vec3(1, 0, 0), Engine::BlockType::Stone));
	_blockMap.push_back(std::make_pair(glm::vec3(0, 1, 0), Engine::BlockType::Stone));
	_blockMap.push_back(std::make_pair(glm::vec3(0, 0, 1), Engine::BlockType::Stone));
}

Rock::~Rock()
{
}
