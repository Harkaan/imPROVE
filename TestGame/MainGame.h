#pragma once

#include <Engine\Scene.h>
#include <Engine\Shader.h>
#include <Engine\InputManager.h>
#include <Engine\TextureCache.h>
#include <Engine\Camera.h>
#include <Engine/Chunk.h>

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
	bool checkBlock(glm::vec3 position);
	std::vector<bool> checkNeighbours(glm::vec3 position);

private:
	Engine::Scene _scene;
	Engine::InputManager _inputManager;
	Engine::Camera _camera;
	GameState _gameState;
	int _worldSize = 16;
	std::vector<Engine::Chunk*> _chunks;

	void gameLoop();
	void checkEnd();
};