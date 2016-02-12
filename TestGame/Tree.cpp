#include "Tree.h"

Tree::Tree(glm::vec3 position) : Structure(position)
{
	_blockMap.push_back(std::make_pair(glm::vec3(0, 0, 0), Engine::BlockType::Wood));
	_blockMap.push_back(std::make_pair(glm::vec3(0, 0, 1), Engine::BlockType::Wood));
	_blockMap.push_back(std::make_pair(glm::vec3(0, 0, 2), Engine::BlockType::Wood));

	const int trunkHeight = 3;

	for (int i = -2; i < 3; i++) {
		for (int j = -2; j < 3; j++) {
			for (int k = trunkHeight; k < trunkHeight + 4; k++) {
				//Structure de base
				if (k < trunkHeight + 2 && (abs(i) + abs(j)) < 4) {
					_blockMap.push_back(std::make_pair(glm::vec3(i, j, k), Engine::BlockType::Leaf));
				}
				//Coins de l'arbre
				else if (k == trunkHeight+1 && randomize(std::make_pair(glm::vec3(i, j, k - 1), Engine::BlockType::Leaf), 75)) {
					randomize(std::make_pair(glm::vec3(i, j, k), Engine::BlockType::Leaf), 25);
				}
				//Feuillage du dessus
				if (k == trunkHeight +2) {
					_blockMap.push_back(std::make_pair(glm::vec3(0, 0, k), Engine::BlockType::Leaf));
					randomize(std::make_pair(glm::vec3(1, 0, k), Engine::BlockType::Leaf), 25);
					randomize(std::make_pair(glm::vec3(0, 1, k), Engine::BlockType::Leaf), 25);
					randomize(std::make_pair(glm::vec3(-1, 0, k), Engine::BlockType::Leaf), 25);
					randomize(std::make_pair(glm::vec3(0, -1, k), Engine::BlockType::Leaf), 25);
				}
				else if (k == trunkHeight +3) {
					randomize(std::make_pair(glm::vec3(0, 0, k), Engine::BlockType::Leaf), 25);
					randomize(std::make_pair(glm::vec3(1, 0, k), Engine::BlockType::Leaf), 10);
					randomize(std::make_pair(glm::vec3(0, 1, k), Engine::BlockType::Leaf), 10);
					randomize(std::make_pair(glm::vec3(-1, 0, k), Engine::BlockType::Leaf), 10);
					randomize(std::make_pair(glm::vec3(0, -1, k), Engine::BlockType::Leaf), 10);
				}
			}
		}
	}
}

Tree::~Tree()
{
}
