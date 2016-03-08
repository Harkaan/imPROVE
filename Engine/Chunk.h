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
		Chunk(glm::vec3 position, int** heightMap);
		~Chunk();

		void init();
		void clear();
		void render();
		void build();		
		void draw();
		void update();

		void addStructure(Structure* structure);
		void addSprite(Sprite* sprite);
		void needsUpdate() { _isUpToDate = false; }
		std::vector<Structure *> getStructures() { return _structures; }
		//std::vector<float> getHeightMap() { return _heightMap; }
		static int noCase(int x, int y);
	
	private:
		glm::vec3 _position;
		int** _heightMap;
		bool _isUpToDate;
		std::vector<Structure*> _structures;

		GLuint _vbo;
		GLuint _vao;
		std::vector<Sprite> _sprites;
		std::vector<Sprite*> _spritePointers;
		std::vector<SpriteBatch> _spriteBatches;

		void createVertexArray();
		void createSpriteBatches();
		void sortSprites();
		void addBlock(Block* block);		
		static bool compareTexture(Sprite* a, Sprite* b);
	};
}

