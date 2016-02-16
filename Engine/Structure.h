#pragma once

#include "Block.h"
#include <random>
#include <map>

namespace Engine
{
	class Structure
	{
	public:
		Structure(glm::vec3 position);
		Structure(const Structure &structure);
		~Structure();

		void build();
		void clear();
		bool randomize(std::pair<glm::vec3, BlockType>, float proba);
		bool addBlock(float x, float y, float z, BlockType blocktype, float proba = 100);

		void setPosition(glm::vec3 position) { _position = position; }
		glm::vec3 getPosition() { return _position; }
		std::vector<Block *> getBlocks() { return _blocks; }

	protected:
		glm::vec3 _position;
		std::vector < std::pair<glm::vec3, BlockType> > _blockMap;
		std::vector<Block*> _blocks;

		std::random_device _rd;
		std::mt19937 _rng;
		std::uniform_int_distribution<int> _uni;
	};
}

