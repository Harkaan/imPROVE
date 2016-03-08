#include "Chunk.h"
#include <algorithm>
#include <iostream>

namespace Engine
{
	Chunk::Chunk(glm::vec3 position, int** heightMap) :
		_position(position),
		_isUpToDate(false),
		_vbo(0), 
		_vao(0)
	{
		_heightMap = new int*[CHUNK_SIZE];
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			_heightMap[i] = new int[CHUNK_SIZE];
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				_heightMap[i][j] = heightMap[i+1][j+1];
			}
		}
	}

	Chunk::~Chunk()
	{
		for (Structure* temp : _structures) {
			delete temp;
		}
		for (int i = 0; i < CHUNK_SIZE; i++) {
			delete _heightMap[i];
		}
		delete _heightMap;

		glDeleteBuffers(1, &_vbo);
		glDeleteVertexArrays(1, &_vao);
	}

	void Chunk::addStructure(Structure* structure)
	{
		glm::vec3 structPosition = structure->getPosition();
		if (structure->isGround()) {
			structure->setPosition(_position);
		}
		else {
			structure->setPosition(structPosition + _position + glm::vec3(0, 0, _heightMap[int(structPosition.x)][int(structPosition.y)]));
		}
		_structures.push_back(structure);
	}

	void Chunk::init()
	{
		createVertexArray();
	}

	void Chunk::clear()
	{
		_spriteBatches.clear();
		_sprites.clear();
	}

	void Chunk::build()
	{
		for (auto structure : _structures) {
			structure->clear();
			structure->build();
			std::vector<Block *> structBlocks = structure->getBlocks();
			for (auto block : structBlocks) {
				addBlock(block);
			}
		}
	}

	void Chunk::render()
	{
		_spritePointers.resize(_sprites.size());
		for (int i = 0; i < _sprites.size(); i++) {
			_spritePointers[i] = &_sprites[i];
		}

		sortSprites();
		createSpriteBatches();
	}

	void Chunk::draw()
	{
		glBindVertexArray(_vao);

		for (int i = 0; i < _spriteBatches.size(); i++) {
			//On bind la texture du SpriteBatch
			glBindTexture(GL_TEXTURE_2D, _spriteBatches[i].texture);

			//On dessine les vertices du SpriteBatch
			glDrawArrays(GL_TRIANGLES, _spriteBatches[i].offset, _spriteBatches[i].numVertices);
		}

		glBindVertexArray(0);
	}

	void Chunk::update()
	{
		if (!_isUpToDate) {
			clear();
			build();
			render();

			_isUpToDate = true;
		}
	}

	void Chunk::createSpriteBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(_spritePointers.size() * 6);

		if (_spritePointers.empty()) {
			return;
		}

		int offset = 0;

		//On crée le premier SpriteBatch, qu'on ajoute directement à _spriteBatches;
		_spriteBatches.emplace_back(offset, 6, _spritePointers[0]->textureID);

		int cv = 0; //current vertex
		vertices[cv++] = _spritePointers[0]->bottomLeft;
		vertices[cv++] = _spritePointers[0]->bottomRight;
		vertices[cv++] = _spritePointers[0]->topLeft;
		vertices[cv++] = _spritePointers[0]->bottomRight;
		vertices[cv++] = _spritePointers[0]->topLeft;
		vertices[cv++] = _spritePointers[0]->topRight;
		offset += 6;

		//On crée les SpritesBatch suivants en loopant dans _spritePointers
		for (int cs = 1; cs < _spritePointers.size(); cs++) { //current sprite
			//On ne crée un nouveau SpriteBatch que si la texture du Sprite actuel est différente du Sprite précédent
			if (_spritePointers[cs]->textureID != _spritePointers[cs - 1]->textureID) {
				_spriteBatches.emplace_back(offset, 6, _spritePointers[cs]->textureID);
			}
			else { //Si la texture est la même que le précédent, on ajoute seulement 6 vertices au batch
				_spriteBatches.back().numVertices += 6;
			}

			//Dans tous les cas, on hydrate les vertices ajoutés
			vertices[cv++] = _spritePointers[cs]->bottomLeft;
			vertices[cv++] = _spritePointers[cs]->bottomRight;
			vertices[cv++] = _spritePointers[cs]->topLeft;
			vertices[cv++] = _spritePointers[cs]->bottomRight;
			vertices[cv++] = _spritePointers[cs]->topLeft;
			vertices[cv++] = _spritePointers[cs]->topRight;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Chunk::createVertexArray()
	{
		if (_vao == 0) {
			glGenVertexArrays(1, &_vao);
		}
		glBindVertexArray(_vao);

		if (_vbo == 0) {
			glGenBuffers(1, &_vbo);
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void Chunk::addBlock(Block * block)
	{
		for (int i = 0; i < block->sprites.size(); i++) {
			addSprite(block->sprites[i]);
		}
	}

	void Chunk::addSprite(Sprite* sprite)
	{
		_sprites.push_back(*sprite);
	}

	void Chunk::sortSprites()
	{
		std::stable_sort(_spritePointers.begin(), _spritePointers.end(), compareTexture);
	}

	bool Chunk::compareTexture(Sprite* a, Sprite* b)
	{
		return (a->textureID < b->textureID);
	}
}
