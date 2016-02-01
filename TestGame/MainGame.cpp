#include "MainGame.h"
#include <Engine\Cube.h>
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
	shader->load();

	//Définition et initialisation des matrices de projection
	glm::mat4 projection;
	glm::mat4 modelview;
	projection = glm::perspective(70.0, 1024.0 / 768.0, 1.0, 100.0);
	modelview = glm::mat4(1.0);

	Engine::Cube cube(shader, &_textureCache.getTexture("Resources/stone.png"));
	cube.render();

	//Boucle principale
	while (_gameState != GameState::EXIT)
	{
		startTicks = SDL_GetTicks();
		
		//Gestion des inputs
		_inputManager.update();
		processInput();

		//Nettoyage de l'écran
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Placement de la caméra
		modelview = glm::lookAt(glm::vec3(10, 7, 5), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1));

		cube.draw(0, 0, 0, projection, modelview);

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
