#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>
#include "Scene.h"

namespace Engine
{
	class Sprite
	{
	public:
		Sprite() { };
		Sprite(std::vector<float> Vertices, std::vector<float> Uv, GLuint TextureID);
		~Sprite();

		void draw();

		std::vector<float> vertices;
		std::vector<float> uv;
		GLuint textureID;
	};
}

