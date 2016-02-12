#pragma once

#include <Engine\Structure.h>
#include <glm\glm.hpp>

class Rock : public Engine::Structure
{
public:
	Rock(glm::vec3 position);
	~Rock();
};

