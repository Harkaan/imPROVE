#include "MainGame.h"
#include "GameStructures.h"
#include "PerlinNoise.h"
#include <Engine\Chunk.h>
#include <Engine\Block.h>

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


MainGame::MainGame() :
	_gameState(GameState::PLAY)
{
}

MainGame::~MainGame()
{
	for (Engine::Chunk* chunk : _chunks) {
		delete chunk;
	}
	_chunks.clear();
}

void MainGame::run()
{
	init();
	gameLoop();
}

// Initialise le contexte OpenGl et la fenêtre à partir du moteur.
void MainGame::init()
{
	_scene.initWindow();
	_scene.initGl();
	_scene.initShaders();
	_camera.init(glm::vec3(-10, -10, 10), glm::vec3(7, 7, -3));
}

// Boucle dans laquelle vit le jeu.
void MainGame::gameLoop()
{
	GLuint frameRate(1000 / 70);
	Uint32 startTicks(0), endTicks(0), elapsedTime(0), startFpsTicks(0), endFpsTicks(0);
	int steps(0);
	int physicalSteps(0);

	Engine::Shader* shader = new Engine::Shader();
	PerlinNoise::initPerlinNoise(15);

	//Hard test
	/*for (int i = 0; i < _worldSize; i++) {
		for (int j = 0; j < _worldSize; j++) {
			int **heightMap;
			heightMap = new int*[CHUNK_SIZE + 2];
			for (int i1 = 0; i1 < CHUNK_SIZE + 2; i1++)
			{
				heightMap[i1] = new int[CHUNK_SIZE + 2];
				for (int j1 = 0; j1 < CHUNK_SIZE + 2; j1++)
				{
					heightMap[i1][j1] = int(1000 * PerlinNoise::getPerlinNoise(i1 + i*CHUNK_SIZE - 1, j1 + j*CHUNK_SIZE - 1, 10000) + 100 * PerlinNoise::getPerlinNoise(i1 + i*CHUNK_SIZE - 1, j1 + j*CHUNK_SIZE - 1, 200));
				}
			}
			Engine::Chunk* chunk = new Engine::Chunk(glm::vec3(i*CHUNK_SIZE, j*CHUNK_SIZE, 0), heightMap);
			chunk->addStructure(new Ground(heightMap));
			chunk->addStructure(new Rock(glm::vec3(2, 6, 0)));
			chunk->addStructure(new Rock(glm::vec3(7, 12, 0)));
			chunk->addStructure(new Tree(glm::vec3(6, 2, 0), rand()%2));
			chunk->init();
			_chunks.emplace_back(chunk);
			for (int i = 0; i < CHUNK_SIZE + 2; i++) {
				delete heightMap[i];
			}
			delete heightMap;
		}
	}*/

	//Soft test
	int **heightMap;
	heightMap = new int*[CHUNK_SIZE + 2];
	for (int i1 = 0; i1 < CHUNK_SIZE + 2; i1++)
	{
		heightMap[i1] = new int[CHUNK_SIZE + 2];
		for (int j1 = 0; j1 < CHUNK_SIZE + 2; j1++)
		{
			heightMap[i1][j1] = int(1000 * PerlinNoise::getPerlinNoise(i1 - 1, j1 - 1, 10000) + 100 * PerlinNoise::getPerlinNoise(i1 - 1, j1 - 1, 200));
		}
	}
	Engine::Chunk* chunk = new Engine::Chunk(glm::vec3(0, 0, 0), heightMap);
	chunk->addStructure(new Ground(heightMap));
	chunk->addStructure(new Source(glm::vec3(7, 7, 0), this));
	chunk->init();
	_chunks.emplace_back(chunk);
	for (int i = 0; i < CHUNK_SIZE + 2; i++) {
		delete heightMap[i];
	}
	delete heightMap;

	//Définition et initialisation des matrices de projection
	glm::mat4 projection;
	glm::mat4 modelview;
	projection = glm::perspective(70.0, (double)WINDOW_WIDTH / WINDOW_HEIGHT, 1.0, 2000.0);
	modelview = glm::mat4(1.0);

	startFpsTicks = SDL_GetTicks();

	//Boucle principale
	while (_gameState != GameState::EXIT)
	{
		startTicks = SDL_GetTicks();
		
		//Gestion des inputs
		_inputManager.update();
		_inputManager.processInput();
		checkEnd();
		_camera.update(_inputManager, modelview);

		//Nettoyage de l'écran
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_scene.getShader().use();	

			glUniformMatrix4fv(glGetUniformLocation(_scene.getShader().getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
			glUniformMatrix4fv(glGetUniformLocation(_scene.getShader().getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));

			//Hard test
			/*for (auto chunk : _chunks) {
				chunk->update();
				chunk->draw();
			}*/

			//Soft test
			physicalSteps++;
			if (physicalSteps % 100 == 0 && physicalSteps < 601) {
				chunk->timeStep();
			}
			
			chunk->update();
			chunk->draw();
			
		_scene.getShader().unuse();

		//Actualisation de la fenêtre
		SDL_GL_SwapWindow(_scene.getWindow());

		//Limitation des FPS
		endTicks = SDL_GetTicks();
		elapsedTime = endTicks - startTicks;
		if (elapsedTime < frameRate) {
			SDL_Delay(frameRate - elapsedTime);
		}

		//Calcul des FPS toutes les 100 frames
		steps++;
		if (steps == 100) {
			endFpsTicks = SDL_GetTicks();
			int fps = steps*1000 / (endFpsTicks - startFpsTicks);
			std::cout << "FPS : " << fps << std::endl;
			steps -= 100;
			startFpsTicks = SDL_GetTicks();
		}
	}
}

bool MainGame::checkBlock(glm::vec3 positionChecked)
{
	int chunkX = (int)positionChecked.x / CHUNK_SIZE;
	int chunkY = (int)positionChecked.y / CHUNK_SIZE;
	int noChunk = chunkY * _worldSize + chunkX;

	for (Engine::Structure* structure : _chunks[noChunk]->getStructures()) {
		for (auto block : structure->getBlockMap())
			if (block.first == positionChecked) {
				// On cherche pour tous les Blocks de toutes les Structures du Chunk susceptible de contenir le Block recherché
				return true;
		}
	}

	return false;
}

std::vector<bool> MainGame::checkNeighbours(glm::vec3 positionChecked)
{
	int chunkX = (int)positionChecked.x / CHUNK_SIZE;
	int chunkY = (int)positionChecked.y / CHUNK_SIZE;
	int noChunk = chunkY * _worldSize + chunkX;

	std::vector<bool> res = { false, false, false, false, false, false };

	for (Engine::Structure* structure : _chunks[noChunk]->getStructures()) {
		for (auto block : structure->getBlockMap()) {
			if (block.first == positionChecked + glm::vec3(0, 0, -1)) {
				res[0] = true;
			}
			else if (block.first == positionChecked + glm::vec3(0, 0, 1)) {
				res[1] = true;
			}
			else if (block.first == positionChecked + glm::vec3(0, -1, 0)) {
				res[2] = true;
			}
			else if (block.first == positionChecked + glm::vec3(0, 1, 0)) {
				res[3] = true;
			}
			else if (block.first == positionChecked + glm::vec3(-1, 0, 0)) {
				res[4] = true;
			}
			else if (block.first == positionChecked + glm::vec3(1, 0, 0)) {
				res[5] = true;
			}
		}
	}

	return res;
}

void MainGame::checkEnd()
{
	if (_inputManager.isKeyDown(SDLK_ESCAPE)) {
		_gameState = GameState::EXIT;
		SDL_QUIT;
	}
}
