#include "Tree.h"

Tree::Tree(glm::vec3 position, int treeType) : Structure(position)
{
	const int trunkHeight = 3;
	switch (treeType) {
		case 0:
			addBlock(0, 0, 0, Engine::BlockType::Wood);
			addBlock(0, 0, 1, Engine::BlockType::Wood);
			addBlock(0, 0, 2, Engine::BlockType::Wood);

			for (int i = -2; i < 3; i++) {
				for (int j = -2; j < 3; j++) {
					for (int k = trunkHeight; k < trunkHeight + 4; k++) {
						//Structure de base
						if (k < trunkHeight + 2 && (abs(i) + abs(j)) < 4) {
							addBlock(i, j, k, Engine::BlockType::Leaf);
						}
						//Coins de l'arbre
						else if (k == trunkHeight + 1 && addBlock(i, j, k - 1, Engine::BlockType::Leaf, 75)) {
							addBlock(i, j, k, Engine::BlockType::Leaf, 25);
						}
						//Feuillage du dessus
						if (k == trunkHeight + 2) {
							addBlock(0, 0, k, Engine::BlockType::Leaf);
							addBlock(1, 0, k, Engine::BlockType::Leaf, 25);
							addBlock(0, 1, k, Engine::BlockType::Leaf, 25);
							addBlock(-1, 0, k, Engine::BlockType::Leaf, 25);
							addBlock(0, -1, k, Engine::BlockType::Leaf, 25);
						}
						else if (k == trunkHeight + 3) {
							addBlock(0, 0, k, Engine::BlockType::Leaf, 25);
							addBlock(1, 0, k, Engine::BlockType::Leaf, 10);
							addBlock(0, 1, k, Engine::BlockType::Leaf, 10);
							addBlock(-1, 0, k, Engine::BlockType::Leaf, 10);
							addBlock(0, -1, k, Engine::BlockType::Leaf, 10);
						}
					}
				}
			}
		break;
		case 1:
			for (int z = 0; z < 11; z++) {
				addBlock(0, 0, z, Engine::BlockType::Wood);
			}
			int xl = 0, yl = 0;
			for (int z = 2; z < 12; z++) {
				if (z == 2) {
					xl = 3;
				}
				else if (z == 9) {
					xl = -1;
				}
				else if (z == 11) {
					xl = 0;
				}
				else {
					xl = 1 + (z % 2);
				}
				for (int x = -xl; x <= xl; x++) {
					if (xl == 1) {
						yl = 1 - abs(x);
					}
					else if (x == 0) {
						yl = xl;
					}
					else {
						yl = xl + 1 - abs(x);
					}
					for (int y = -yl; y <= yl; y++) {
						addBlock(x, y, z, Engine::BlockType::Leaf);
					}
				}
			}
			break;
		}
}

Tree::~Tree()
{
}
