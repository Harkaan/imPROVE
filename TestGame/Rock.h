#pragma once

#include <Engine\Structure.h>
#include <glm\glm.hpp>
#include <map>

class Rock : public Engine::Structure
{
public:
	Rock(glm::vec3 position);
	~Rock();
};

