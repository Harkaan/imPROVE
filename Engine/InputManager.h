#pragma once

#include <SDL\SDL.h>
#include <unordered_map>
#include <glm\glm.hpp>

namespace Engine
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void processInput();
		void update();
		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);
		bool isKeyDown(unsigned int keyID); //true si la touche est maintenue appuyée
		bool isKeyPressed(unsigned int keyID); //true si la touche vient d'être enfoncée
		bool mouseMoved() const;

		//Setters et getters
		void setMouseCoords(float x, float y) { _mouseCoords.x = x; _mouseCoords.y = y; }
		void setMouseMoves(float x, float y) { _mouseMoves.x = x; _mouseMoves.y = y; }
		glm::vec2 getMouseCoords() const { return _mouseCoords; }
		glm::vec2 getMouseMoves() const { return _mouseMoves; }

	private:
		bool wasKeyDown(unsigned int keyID); //true si la touche était enfoncée précédemment		

		SDL_Event _event;
		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _previousKeyMap;
		glm::vec2 _mouseCoords;
		glm::vec2 _mouseMoves;
	};
}
