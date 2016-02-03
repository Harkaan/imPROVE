#include "MainGame.h"
#include <Engine\Block.h>
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

// Initialise le contexte OpenGl et la fenêtre à partir du moteur.
void MainGame::init()
{
	_scene.initWindow();
	_scene.initGl();
	_scene.initShaders();
}

void MainGame::run()
{
	init();
	gameLoop();
}

// Boucle dans laquelle vit le jeu.
void MainGame::gameLoop()
{
	GLuint frameRate(1000 / 50);
	Uint32 startTicks(0), endTicks(0), elapsedTime(0);

	Engine::Shader* shader = new Engine::Shader();

	std::vector<Engine::Block> blocks;

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			blocks.emplace_back(glm::vec3(i, j, 0), Engine::BlockType::Grass);
		}
	}

	//Définition et initialisation des matrices de projection
	glm::mat4 projection;
	glm::mat4 modelview;
	projection = glm::perspective(70.0, 1024.0 / 768.0, 1.0, 100.0);
	modelview = glm::lookAt(glm::vec3(20, -16, 6), glm::vec3(8, 8, 1), glm::vec3(0, 0, 1));

	//Boucle principale
	while (_gameState != GameState::EXIT)
	{
		startTicks = SDL_GetTicks();
		
		//Gestion des inputs
		_inputManager.update();
		processInput();

		//Nettoyage de l'écran
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_scene.getShader().use();	

			glUniformMatrix4fv(glGetUniformLocation(_scene.getShader().getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
			glUniformMatrix4fv(glGetUniformLocation(_scene.getShader().getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));

			for (auto block:blocks) {
				block.draw();
			}

		_scene.getShader().unuse();

		//Actualisation de la fenêtre
		SDL_GL_SwapWindow(_scene.getWindow());

		//Limitation des FPS
		endTicks = SDL_GetTicks();
		elapsedTime = endTicks - startTicks;
		if (elapsedTime < frameRate) {
			SDL_Delay(frameRate - elapsedTime);
		}
	}
}

void MainGame::processInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(event.key.keysym.sym);
			break;
		}
	}
}
