#pragma once
#include <Engine\Structure.h>
#include <glm\glm.hpp>
#include <map>

class Tree :
	public Engine::Structure
{
public:
	Tree(glm::vec3 position);
	~Tree();
};

