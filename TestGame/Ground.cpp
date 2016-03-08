#include "Ground.h"
#include <algorithm> 
#include <iostream>

Ground::Ground(int** heightMap) : Structure(glm::vec3(0, 0, 0))
{
	_isGround = true;
	int m_tailleChunk = 16;
	int m = 0;
	int **dHeight;
	dHeight = new int*[m_tailleChunk + 2];
	for (int i = 0; i < m_tailleChunk + 2; i++)
	{
		dHeight[i] = new int[m_tailleChunk + 2];
		for (int j = 0; j < m_tailleChunk + 2; j++)
		{
			dHeight[i][j] = 1;
		}
	}
	for (int i = 1; i < m_tailleChunk + 1; i++)
	{
		for (int j = 1; j < m_tailleChunk + 1; j++)
		{
			m = std::min(std::min(std::min(heightMap[i + 1][j], heightMap[i - 1][j]), heightMap[i][j - 1]), heightMap[i][j + 1]);
			if (m + 1 < heightMap[i][j])
			{
				dHeight[i][j] = heightMap[i][j] - m;
			}
		}
	}

	for (int i = 1; i < m_tailleChunk + 1; i++)
	{
		for (int j = 1; j < m_tailleChunk + 1; j++)
		{
			for (int k = 0; k < dHeight[i][j]; k++)
			{
				addBlock(i - 1, j - 1, heightMap[i][j] + k - 1, Engine::BlockType::Grass);
			}
		}
	}
	for (int i = 0; i < m_tailleChunk + 2; i++) {
		delete dHeight[i];
	}	
	delete dHeight;
}


Ground::~Ground()
{

}
