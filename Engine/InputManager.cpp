#include "InputManager.h"

namespace Engine
{
	InputManager::InputManager() : 
		_mouseCoords(0.0f, 0.0f)
	{
	}

	InputManager::~InputManager()
	{
	}

	//Met � jour la _previousKeyMap avec les valeurs de l'actuelle _keyMap.
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

	//Renvoie true si la touche keyID est maintenue enfonc�e.
	bool InputManager::isKeyDown(unsigned int keyID)
	{
		auto it = _keyMap.find(keyID); //it est un couple (indice ; isDown)
		if (it != _keyMap.end()) { //si l'indice keyID existe
			return it->second; //on renvoie la deuxi�me valeur de l'indice trouv�, c'est � dire le bool�en isDown
		}
		else { //s'il n'existe pas
			return false;
		}
	}

	//Renvoie true si la touche keyID vient d'�tre enfonc�e.
	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		if (isKeyDown(keyID) && !wasKeyDown(keyID)) {
			return true;
		}
		return false;
	}

	//Renvoie true si la touche keyID �tait enfonc�e � la frame pr�c�dente (ie dans _previousKeyMap).
	bool InputManager::wasKeyDown(unsigned int keyID)
	{
		auto it = _previousKeyMap.find(keyID); //it est un couple (indice ; isDown)
		if (it != _previousKeyMap.end()) { //si l'indice keyID existe
			return it->second; //on renvoie la deuxi�me valeur de l'indice trouv�, c'est � dire le bool�en isDown
		}
		else { //s'il n'existe pas
			return false;
		}
	}
}