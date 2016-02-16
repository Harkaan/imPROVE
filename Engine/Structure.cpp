#include "Structure.h"
#include <iostream>

namespace Engine
{
	Structure::Structure(glm::vec3 position) :
		_position(position),
		_rng(_rd()),
		_uni(1, 100)
	{
	}

	Structure::Structure(const Structure &structure)
	{
		_position = structure._position;
		_blockMap = structure._blockMap;
		_blocks = structure._blocks;
	}

	Structure::~Structure()
	{
		for (Block* temp : _blocks) {
			delete temp;
		}
	}

	//Cette fonction va créer un tableau 3D contenant, pour chaque coordonnée, le type de bloc que contient la structure (Void s'il n'y a rien).
	//Puis elle va utiliser ce tableau pour que chacun des blocs ne soit créé qu'avec le nombre minimum de faces.
	void Structure::build() 
	{
		int minX = _blockMap[0].first.x, minY = _blockMap[0].first.y, minZ = _blockMap[0].first.z, maxX = minX, maxY = minY, maxZ = minZ; 
		for (auto temp : _blockMap) {
				maxX = maxX + (temp.first.x - maxX)*(temp.first.x > maxX);
				minX = minX + (temp.first.x - minX)*(temp.first.x < minX);
				maxY = maxY + (temp.first.y - maxY)*(temp.first.y > maxY);
				minY = minY + (temp.first.y - minY)*(temp.first.y < minY);
				maxZ = maxZ + (temp.first.z - maxZ)*(temp.first.z > maxZ);
				minZ = minZ + (temp.first.z - minZ)*(temp.first.z < minZ);
		}
		BlockType ***blockMap;
		blockMap = new BlockType**[maxX - minX + 1];
		for (int i = 0; i < maxX - minX + 1; i++) {
			blockMap[i] = new BlockType*[maxY - minY + 1];
			for (int j = 0; j < maxY - minY + 1; j++) {
				blockMap[i][j] = new BlockType[maxZ - minZ + 1];
				for (int k = 0; k < maxZ - minZ + 1; k++) {
					blockMap[i][j][k] = BlockType::Void;
				}
			}
		}
		for (auto temp : _blockMap) {
			blockMap[(int)temp.first.x - minX][(int)temp.first.y - minY][(int)temp.first.z - minZ] = temp.second;
		}
		bool spritesLoaded[6];
		for (int i = 0; i < maxX - minX + 1; i++) {
			for (int j = 0; j < maxY - minY + 1; j++) {
				for (int k = 0; k < maxZ - minZ + 1; k++) {
					if (blockMap[i][j][k] != BlockType::Void) {
						for (int p = 0; p < 6; p++) {
							spritesLoaded[p] = true;
						}
						if (i != 0) {
							spritesLoaded[4] = (blockMap[i - 1][j][k] == BlockType::Void);
						}
						if (i != maxX - minX) {
							spritesLoaded[5] = (blockMap[i + 1][j][k] == BlockType::Void);
						}
						if (j != 0) {
							spritesLoaded[2] = (blockMap[i][j - 1][k] == BlockType::Void);
						}
						if (j != maxY - minY) {
							spritesLoaded[3] = (blockMap[i][j + 1][k] == BlockType::Void);
						}
						if (k != 0) {
							spritesLoaded[0] = (blockMap[i][j][k - 1] == BlockType::Void);
						}
						if (k != maxZ - minZ) {
							spritesLoaded[1] = (blockMap[i][j][k + 1] == BlockType::Void);
						}
						_blocks.push_back(new Block(glm::vec3(i + minX, j + minY, k + minZ) + _position, spritesLoaded, blockMap[i][j][k]));
					}
				}
			}
		}
		for (int i = 0; i < maxX - minX + 1; i++) {
			for (int j = 0; j < maxY - minY + 1; j++) {
				delete blockMap[i][j];
			}
			delete blockMap[i];
		}
		delete blockMap;
	}

	void Structure::clear()
	{
		_blocks.clear();
	}

	bool Structure::randomize(std::pair<glm::vec3, BlockType> dataPair, float proba)
	{
		if (_uni(_rng) < proba) {
			_blockMap.push_back(dataPair);
			return true;
		}
		return false;
	}

	bool Structure::addBlock(float x, float y, float z, BlockType blocktype, float proba)
	{
		return randomize(std::make_pair(glm::vec3(x, y, z), blocktype), proba);
	}
}
