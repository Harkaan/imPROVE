#include "Source.h"


Source::Source(glm::vec3 position, MainGame* maingame) : Structure(position)
{
	_mainGame = maingame;
	addSource(0, 0, 0);
}

Source::~Source()
{
}

bool Source::flow()
{
	bool chunkNeedsUpdate = false;
	std::vector<glm::vec3> newSources;

	for (int i = 0; i < _blockMap.size(); i++) {
		if (_blockMap[i].second == Engine::BlockType::Source) {
			std::vector<bool> neighbours = _mainGame->checkNeighbours(_blockMap[i].first + _position); //bottom, up, back, front, left, right
			if (!neighbours[0]) {
				newSources.push_back(_blockMap[i].first + glm::vec3(0, 0, -1));
				chunkNeedsUpdate = true;
			}
			else {
				if (!neighbours[2]) {
					newSources.push_back(_blockMap[i].first + glm::vec3(0, -1, 0));
					chunkNeedsUpdate = true;
				}
				if (!neighbours[3]) {
					newSources.push_back(_blockMap[i].first + glm::vec3(0, 1, 0));
					chunkNeedsUpdate = true;
				}
				if (!neighbours[4]) {
					newSources.push_back(_blockMap[i].first + glm::vec3(-1, 0, 0));
					chunkNeedsUpdate = true;
				}
				if (!neighbours[5]) {
					newSources.push_back(_blockMap[i].first + glm::vec3(1, 0, 0));
					chunkNeedsUpdate = true;
				}
			}

			_blockMap[i].second = Engine::BlockType::Water;
		}
	}

	for (auto source : newSources) {
		addSource(source.x, source.y, source.z);
	}

	return chunkNeedsUpdate;
}

bool Source::timeStep()
{
	return flow();
}

void Source::addSource(float x, float y, float z, int proba)
{
	addBlock(x, y, z, Engine::BlockType::Source, proba);
}
