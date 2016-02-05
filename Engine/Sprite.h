#pragma once

#include "Vertex.h"
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <vector>

namespace Engine
{
	class Sprite
	{
	public:
		Sprite();
		Sprite(const std::vector<glm::vec3>& coords, const ColorRGBA& color, const std::vector<float>& uvRect, GLuint Texture) :
			textureID(Texture)
		{
			bottomLeft.color = color;
			bottomLeft.setPosition(coords[0].x, coords[0].y, coords[0].z);
			bottomLeft.setUV(uvRect[0], uvRect[1]);

			bottomRight.color = color;
			bottomRight.setPosition(coords[1].x, coords[1].y, coords[1].z);
			bottomRight.setUV(uvRect[0] + uvRect[2], uvRect[1]);

			topLeft.color = color;
			topLeft.setPosition(coords[2].x, coords[2].y, coords[2].z);
			topLeft.setUV(uvRect[0], uvRect[1] + uvRect[3]);

			topRight.color = color;
			topRight.setPosition(coords[3].x, coords[3].y, coords[3].z);
			topRight.setUV(uvRect[0] + uvRect[2], uvRect[1] + uvRect[3]);
		}

		GLuint textureID;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};
}

