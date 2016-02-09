#pragma once

#include <Engine\Scene.h>
#include <Engine\Shader.h>
#include <Engine\InputManager.h>
#include <Engine\Camera.h>
#include <Engine\Input.h>
#include <Engine\TextureCache.h>

enum class GameState {
	PLAY,
	EXIT
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();
	void init();

private:
	Engine::Scene _scene;
	Engine::InputManager _inputManager;
	GameState _gameState;
	float _theta;
	Engine::Input m_input;

	void gameLoop();
	void processInput();
	void processBasicCamera();
};