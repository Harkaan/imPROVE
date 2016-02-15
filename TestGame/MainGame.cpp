#include "MainGame.h"
#include <Engine\Chunk.h>
#include <Engine\Block.h>
#include "GameStructures.h"
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

	Engine::Shader* shader = new Engine::Shader();

	std::vector<float> heightmap = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
									1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

	//Hard test
	std::vector<Engine::Chunk*> chunks;
	for(int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			Engine::Chunk* chunk = new Engine::Chunk(glm::vec3(i*16 , j*16, 0), Engine::BlockType::Grass, heightmap);
			chunk->addStructure(new Rock(glm::vec3(2, 6, 0)));
			chunk->addStructure(new Rock(glm::vec3(7, 12, 0)));
			chunk->addStructure(new Tree(glm::vec3(6, 2, 0)));
			chunk->init();
			chunks.emplace_back(chunk);
		}
	}

	//Soft test
	/*Engine::Chunk* chunk = new Engine::Chunk(glm::vec3(0, 0, 0), Engine::BlockType::Grass, heightmap);
	Engine::Chunk* chunk2 = new Engine::Chunk(glm::vec3(16, 0, 0), Engine::BlockType::Water, heightmap);
	chunk->addStructure(new Rock(glm::vec3(2, 6, 0)));
	chunk->addStructure(new Rock(glm::vec3(7, 12, 0)));
	chunk->addStructure(new Tree(glm::vec3(6, 2, 0)));
	chunk->init();
	chunk2->init();*/

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
				for (auto chunk : chunks) {
					chunk->update();
					chunk->draw();
				}

				//Soft test
				/*chunk->update();
				chunk->draw();

				chunk2->update();
				chunk2->draw();*/
			
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

void MainGame::checkEnd()
{
	if (_inputManager.isKeyDown(SDLK_ESCAPE)) {
		_gameState = GameState::EXIT;
		SDL_QUIT;
	}
}
