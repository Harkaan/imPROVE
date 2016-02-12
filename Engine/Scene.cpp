#include "Scene.h"
#include <iostream>

namespace Engine
{
	Scene::Scene() :
		_windowWidth(WINDOW_WIDTH),
		_windowHeight(WINDOW_HEIGHT),
		_shaders(),
		_window(0),
		_glContext(0)
	{
	}

	Scene::~Scene()
	{
		SDL_GL_DeleteContext(_glContext);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}

	bool Scene::initWindow()
	{
		// Initialisation de la SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cout << "ERROR : SDL failed to be initialized : " << SDL_GetError() << std::endl;
			SDL_Quit();
			return false;
		}

		//// Version d'OpenGL
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		// Double Buffer
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		// Création de la fenêtre
		_window = SDL_CreateWindow(_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _windowWidth, _windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		if (_window == 0) {
			std::cout << "ERROR : Window failed to be created : " << SDL_GetError() << std::endl;
			SDL_Quit();
			return false;
		}

		// Création du contexte OpenGL
		_glContext = SDL_GL_CreateContext(_window);
		if (_glContext == 0) {	
			std::cout << SDL_GetError() << std::endl;
			SDL_DestroyWindow(_window);
			SDL_Quit();
			return false;
		}

		return true;
	}

	bool Scene::initGl()
	{
		//Initialise Glew
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{
			// On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)
			std::cout << "ERROR : GLEW failed to be initialized : " << glewGetErrorString(glewError) << std::endl;
			// On quitte la SDL
			SDL_GL_DeleteContext(_glContext);
			SDL_DestroyWindow(_window);
			SDL_Quit();
			return false;
		}

		//Log de la version d'OpenGL qui a été initialisée
		std::printf("***** OpenGL Version : %s *****\n", glGetString(GL_VERSION));

		//Active et configure le rendu de la transparence
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return true;
	}

	void Scene::initShaders()
	{
		_shaders.load();
	}
}
