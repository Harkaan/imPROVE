#pragma once

#include "Structure.h"
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <vector>

const int CHUNK_SIZE = 16;

namespace Engine
{
	class SpriteBatch
	{
	public:
		SpriteBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture) {}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class Chunk
	{	
	public:
		Chunk(glm::vec3 position, BlockType blocktype, float heightmap[CHUNK_SIZE * CHUNK_SIZE]);
		~Chunk();

		void addStructure(Structure* structure);
		void addSprite(Sprite* sprite);
		void init();
		void clear();
		void render();
		void build();		
		void draw();
	
	private:
		glm::vec3 _position;
		float _heightMap[CHUNK_SIZE * CHUNK_SIZE];
		
		std::vector<Structure*> _structures;
		std::vector<Block*> _groundBlocks;

		GLuint _vbo;
		GLuint _vao;
		std::vector<Sprite> _sprites;
		std::vector<Sprite*> _spritePointers;
		std::vector<SpriteBatch> _spriteBatches;

		void createVertexArray();
		void createSpriteBatches();
		void sortSprites();
		void addBlock(Block* block);
		int noCase(int x, int y);
		static bool compareTexture(Sprite* a, Sprite* b);
	};
}

