#include "InputManager.h"

namespace Engine
{
	InputManager::InputManager() :
		_mouseCoords(0.0f, 0.0f),
		_mouseMoves(0.0f, 0.0f)
	{
	}

	InputManager::~InputManager()
	{
	}

	void InputManager::processInput()
	{
		_mouseMoves = glm::vec2(0);

		while (SDL_PollEvent(&_event)) {
			switch (_event.type) {
			case SDL_MOUSEMOTION:
				setMouseCoords(_event.motion.x, _event.motion.y);
				setMouseMoves(_event.motion.xrel, _event.motion.yrel);
				break;
			case SDL_KEYDOWN:
				pressKey(_event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				releaseKey(_event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				pressKey(_event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				releaseKey(_event.button.button);
				break;
			default:
				break;
			}
		}
	}

	//Met à jour la _previousKeyMap avec les valeurs de l'actuelle _keyMap.
	void InputManager::update()
	{
		for (auto& it : _keyMap) {
			_previousKeyMap[it.first] = it.second;
		}
	}

	void InputManager::pressKey(unsigned int keyID)
	{
		_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID)
	{
		_keyMap[keyID] = false;
	}

	//Renvoie true si la touche keyID est maintenue enfoncée.
	bool InputManager::isKeyDown(unsigned int keyID)
	{
		auto it = _keyMap.find(keyID); //it est un couple (indice ; isDown)
		if (it != _keyMap.end()) { //si l'indice keyID existe
			return it->second; //on renvoie la deuxième valeur de l'indice trouvé, c'est à dire le booléen isDown
		}
		else { //s'il n'existe pas
			return false;
		}
	}

	//Renvoie true si la touche keyID vient d'être enfoncée.
	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		if (isKeyDown(keyID) && !wasKeyDown(keyID)) {
			return true;
		}
		return false;
	}

	//Renvoie true si la touche keyID était enfoncée à la frame précédente (ie dans _previousKeyMap).
	bool InputManager::wasKeyDown(unsigned int keyID)
	{
		auto it = _previousKeyMap.find(keyID); //it est un couple (indice ; isDown)
		if (it != _previousKeyMap.end()) { //si l'indice keyID existe
			return it->second; //on renvoie la deuxième valeur de l'indice trouvé, c'est à dire le booléen isDown
		}
		else { //s'il n'existe pas
			return false;
		}
	}

	bool InputManager::mouseMoved() const
	{
		return !(_mouseMoves == glm::vec2(0));
	}
}