#pragma once

#include <GL\glew.h>
#include <string>
#include <vector>

namespace Engine
{
	struct Texture
	{
		GLuint id;
		int width;
		int height;

		static Texture loadPNG(std::string filePath);
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};
}

