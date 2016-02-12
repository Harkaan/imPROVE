#pragma once

#include <Engine\Scene.h>
#include <Engine\Shader.h>
#include <Engine\InputManager.h>
#include <Engine\TextureCache.h>
#include <Engine\Camera.h>

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
	Engine::Camera _camera;
	GameState _gameState;

	void gameLoop();
	void checkEnd();
};