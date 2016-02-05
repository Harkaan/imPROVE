#include "MainGame.h"
#include <Engine\Chunk.h>
#include <Engine\Block.h>
#include "Rock.h"
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

MainGame::MainGame() :
	_gameState(GameState::PLAY),
	_theta(0)
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
	Uint32 startTicks(0), endTicks(0), elapsedTime(0), startFpsTicks(0), endFpsTicks(0);
	int steps(0);

	Engine::Shader* shader = new Engine::Shader();

	float heightmap[CHUNK_SIZE*CHUNK_SIZE] = {  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };

	Engine::Chunk* chunk = new Engine::Chunk(glm::vec3(0, 0, 0), Engine::BlockType::Grass, heightmap);
	chunk->addStructure(new Rock(glm::vec3(2, 6, 0)));
	chunk->addStructure(new Rock(glm::vec3(7, 12, 0)));
	chunk->init();

	//Définition et initialisation des matrices de projection
	glm::mat4 projection;
	glm::mat4 modelview;
	projection = glm::perspective(70.0, 1024.0 / 768.0, 1.0, 100.0);
	modelview = glm::mat4(1.0);

	startFpsTicks = SDL_GetTicks();

	//Boucle principale
	while (_gameState != GameState::EXIT)
	{
		startTicks = SDL_GetTicks();
		
		//Gestion des inputs
		_inputManager.update();
		processInput();
		processBasicCamera();

		modelview = glm::lookAt(glm::vec3(8 + 30*cos(_theta), 8 + 30*sin(_theta), 10), glm::vec3(8, 8, 2), glm::vec3(0, 0, 1));

		//Nettoyage de l'écran
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_scene.getShader().use();	

			glUniformMatrix4fv(glGetUniformLocation(_scene.getShader().getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
			glUniformMatrix4fv(glGetUniformLocation(_scene.getShader().getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));

			chunk->clear();
			chunk->render();
			chunk->build();
			chunk->draw();

		_scene.getShader().unuse();

		//Actualisation de la fenêtre
		SDL_GL_SwapWindow(_scene.getWindow());

		//Limitation des FPS
		endTicks = SDL_GetTicks();
		elapsedTime = endTicks - startTicks;
		if (elapsedTime < frameRate) {
			//SDL_Delay(frameRate - elapsedTime);
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

void MainGame::processBasicCamera()
{
	if (_inputManager.isKeyDown(SDLK_d)) {
		_theta += 0.1;
	}
	else if (_inputManager.isKeyDown(SDLK_q)) {
		_theta -= 0.1;
	}

}
