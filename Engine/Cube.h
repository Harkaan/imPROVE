#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"
#include <vector>

namespace Engine
{
	class Cube
	{
	public:
		const int CUBE_VERTICES_SIZE_BYTES = 108 * sizeof(float);
		const int TEXTURE_UV_SIZE_Bytes = 72 * sizeof(float);

		Cube(Shader* shader, Texture* texture);
		~Cube();
		void draw(float x, float y, float z, glm::mat4 &projection, glm::mat4 &modelview);
		void render();

	private:
		Shader* _shader;
		std::vector<float> _vertices;
		std::vector<float> _uv;
		Texture* _texture;

		GLuint _vboID;
		GLuint _vaoID;
	};
}

