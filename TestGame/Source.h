#pragma once

#include <Engine\Structure.h>
#include "MainGame.h"
#include <glm\glm.hpp>
#include <thread>

class Source : public Engine::Structure
{
public:
	Source(glm::vec3 position, MainGame* maingame);
	~Source();

	void addSource(float x, float y, float z, int proba = 100);
	bool flow();
	bool timeStep();

private:
	MainGame* _mainGame;
	std::vector<bool> checkNeighbours(glm::vec3 position);
};

