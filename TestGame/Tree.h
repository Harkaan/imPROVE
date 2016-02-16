#pragma once

#include <Engine\Structure.h>

class Tree : public Engine::Structure
{
public:
	Tree(glm::vec3 position, int treeType);
	~Tree();
};

