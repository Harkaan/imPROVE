#include "Rock.h"
#include <vector>
#include <Engine\Block.h>


Rock::Rock(glm::vec3 position) : Structure(position)
{
	addBlock(0, 0, 0, Engine::BlockType::Stone);
	addBlock(1, 0, 0, Engine::BlockType::Stone, 60);
	addBlock(0, 1, 0, Engine::BlockType::Stone, 60);
	addBlock(-1, 0, 0, Engine::BlockType::Stone, 60);
	addBlock(0, -1, 0, Engine::BlockType::Stone, 60);

	if (addBlock(0, 0, 1, Engine::BlockType::Stone, 40)) {
		addBlock(0, 0, 2, Engine::BlockType::Stone, 20);
	}
}

Rock::~Rock()
{
}
