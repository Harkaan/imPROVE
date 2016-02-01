#pragma once

#include <string>
#include <GL/glew.h>
#include <SDL\SDL.h>
#include "Shader.h"

namespace Engine
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		bool initWindow();
		bool initGl();
		void initShaders();

		SDL_Window* getWindow(){ return _window; };
		Engine::Shader getShader(){ return _shaders; };

	private:
		std::string _windowTitle;
		int _windowWidth, _windowHeight;

		Engine::Shader _shaders;
		SDL_Window* _window;
		SDL_GLContext _glContext;
		SDL_Event _events;
	};
}

