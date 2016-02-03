#include "Sprite.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
	Sprite::Sprite(std::vector<float> Vertices, std::vector<float> Uv, GLuint TextureID) :
		vertices(Vertices),
		uv(Uv),
		textureID(TextureID)
	{
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::draw()
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, uv.data());

		glBindTexture(GL_TEXTURE_2D, textureID);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
