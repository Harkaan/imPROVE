#pragma once

#include <Engine\Structure.h>
#include <glm\glm.hpp>

class Ground : public Engine::Structure
{
public:
	Ground(int** heightMap);
	~Ground();
};

