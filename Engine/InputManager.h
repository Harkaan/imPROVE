#pragma once

#include <unordered_map>
#include <glm\glm.hpp>

namespace Engine
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();
		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);
		bool isKeyDown(unsigned int keyID); //true si la touche est maintenue appuy�e
		bool isKeyPressed(unsigned int keyID); //true si la touche vient d'�tre enfonc�e

		//Setters et getters
		void setMouseCoords(float x, float y) { _mouseCoords.x = x; _mouseCoords.y = y; }
		glm::vec2 getMouseCoords() const { return _mouseCoords; };

	private:
		bool wasKeyDown(unsigned int keyID); //true si la touche �tait enfonc�e pr�c�demment		

		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _previousKeyMap;
		glm::vec2 _mouseCoords;
	};
}
