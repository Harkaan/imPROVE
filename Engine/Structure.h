#pragma once

#include "Block.h"

namespace Engine
{
	class Structure
	{
	public:
		Structure(glm::vec3 position);
		Structure(const Structure &structure);
		~Structure();

		void build();

		void setPosition(glm::vec3 position) { _position = position; }
		glm::vec3 getPosition() { return _position; }
		std::vector<Block *> getBlocks() { return _blocks; }

	protected:
		glm::vec3 _position;
		std::vector < std::pair<glm::vec3, BlockType> > _blockMap;
		std::vector<Block*> _blocks;
	};
}

