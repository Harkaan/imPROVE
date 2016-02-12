#include "Tree.h"


Tree::Tree(glm::vec3 position) : Structure(position)
{
	_blockMap.push_back(std::make_pair(glm::vec3(0, 0, 0), Engine::BlockType::Wood));
	_blockMap.push_back(std::make_pair(glm::vec3(0, 0, 1), Engine::BlockType::Wood));
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			_blockMap.push_back(std::make_pair(glm::vec3(-2 + i, -2 + j, 2), Engine::BlockType::Leaves));
			if (i == 0 || i == 4) {
				if (j == 0 || j == 4) {
				}
				else {
					_blockMap.push_back(std::make_pair(glm::vec3(-2 + i, -2 + j, 3), Engine::BlockType::Leaves));
				}
			}
			else {
				_blockMap.push_back(std::make_pair(glm::vec3(-2 + i, -2 + j, 3), Engine::BlockType::Leaves));
			}
		}
	}
	_blockMap.push_back(std::make_pair(glm::vec3(-2, 0, 2), Engine::BlockType::Leaves));
	for (int i = 0; i < 2; i++) {
		_blockMap.push_back(std::make_pair(glm::vec3(-1, 0, 4 + i), Engine::BlockType::Leaves));
		_blockMap.push_back(std::make_pair(glm::vec3(0, 0, 4 + i), Engine::BlockType::Leaves));
		_blockMap.push_back(std::make_pair(glm::vec3(1, 0, 4 + i), Engine::BlockType::Leaves));
		_blockMap.push_back(std::make_pair(glm::vec3(0, -1, 4 + i), Engine::BlockType::Leaves));
		_blockMap.push_back(std::make_pair(glm::vec3(0, 1, 4 + i), Engine::BlockType::Leaves));
	}
}


Tree::~Tree()
{
}
