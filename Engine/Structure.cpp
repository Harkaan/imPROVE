#include "Structure.h"

namespace Engine
{
	Structure::Structure(glm::vec3 position) :
		_position(position),
		_rng(_rd()),
		_uni(1, 100)
	{
	}

	Structure::Structure(const Structure &structure)
	{
		_position = structure._position;
		_blockMap = structure._blockMap;
		_blocks = structure._blocks;
	}

	Structure::~Structure()
	{
		for (Block* temp : _blocks) {
			delete temp;
		}
	}

	void Structure::build() 
	{
		for (auto temp : _blockMap) {
			_blocks.push_back(new Block(temp.first + _position, temp.second));
		}
	}

	void Structure::clear()
	{
		_blocks.clear();
	}

	bool Structure::randomize(std::pair<glm::vec3, BlockType> dataPair, float proba)
	{
		if (_uni(_rng) < proba) {
			_blockMap.push_back(dataPair);
			return true;
		}
		return false;
	}
}
