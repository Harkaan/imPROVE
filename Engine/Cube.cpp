#include "Cube.h"

namespace Engine
{
	Cube::Cube(Shader* shader, Texture* texture) : _shader(shader), _texture(texture), _vboID(0), _vaoID(0)
	{
		float verticesTmp[] = { 1, 0, 1,  1, 0, 0,  1, 1, 0,  //DROITE
								1, 0, 1,  1, 1, 1,  1, 1, 0,  //DROITE
								0, 0, 0,  1, 0, 0,  1, 1, 0,  //DEVANT
								0, 0, 0,  0, 1, 0,  1, 1, 0,  //DEVANT
								0, 0, 0,  0, 0, 1,  0, 1, 1,  //GAUCHE
								0, 0, 0,  0, 1, 0,  0, 1, 1,  //GAUCHE
								0, 0, 1,  1, 0, 1,  1, 1, 1,  //DERRIERE
								0, 0, 1,  0, 1, 1,  1, 1, 1,  //DERRIERE
								0, 1, 1,  1, 1, 1,  1, 1, 0,  //HAUT
								0, 1, 1,  0, 1, 0,  1, 1, 0,  //HAUT
								0, 0, 1,  1, 0, 1,  1, 0, 0,  //BAS
								0, 0, 1,  0, 0, 0,  1, 0, 0 };//BAS

		float coordTextureTmp[] = { 0, 1,  0, 0,  1, 0,  //DROITE
									0, 1,  1, 1,  1, 0,  //DROITE
									0, 0,  1, 0,  1, 1,  //DEVANT
									0, 0,  0, 1,  1, 1,  //DEVANT
									0, 0,  0, 1,  1, 1,  //GAUCHE
									0, 0,  1, 0,  1, 1,  //GAUCHE
									0, 0,  1, 0,  1, 1,  //DERRIERE
									0, 0,  0, 1,  1, 1,  //DERRIERE
									0, 1,  1, 1,  1, 0,  //HAUT
									0, 1,  0, 0,  1, 0,  //HAUT
									0, 0,  1, 0,  1, 1,  //BAS
									0, 0,  0, 1,  1, 1 };//BAS

		for (int i = 0; i < 108; i++)
		{
			_vertices.push_back(verticesTmp[i]);
			if (i < 72)
				_uv.push_back(coordTextureTmp[i]);
		}
	}

	Cube::~Cube()
	{
		glDeleteBuffers(1, &_vboID);
		glDeleteVertexArrays(1, &_vaoID);
	}

	void Cube::draw(float x, float y, float z, glm::mat4 &projection, glm::mat4 &modelview)
	{
		_shader->use();

			glm::mat4 modelviewSave = modelview;
			modelview = glm::translate(modelview, glm::vec3(x, y, z));

			glBindVertexArray(_vaoID);
			glUniformMatrix4fv(glGetUniformLocation(_shader->getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
			glUniformMatrix4fv(glGetUniformLocation(_shader->getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
			glBindTexture(GL_TEXTURE_2D, _texture->id);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);

			modelview = modelviewSave;

		_shader->unuse();
	}

	void Cube::render()
	{
		if (glIsBuffer(_vboID) == GL_TRUE)
			glDeleteBuffers(1, &_vboID);
		glGenBuffers(1, &_vboID);
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		glBufferData(GL_ARRAY_BUFFER, CUBE_VERTICES_SIZE_BYTES + TEXTURE_UV_SIZE_Bytes, 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, CUBE_VERTICES_SIZE_BYTES, &_vertices[0]);
		glBufferSubData(GL_ARRAY_BUFFER, CUBE_VERTICES_SIZE_BYTES, TEXTURE_UV_SIZE_Bytes, &_uv[0]);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (glIsVertexArray(_vaoID) == GL_TRUE)
			glDeleteVertexArrays(1, &_vaoID);
		glGenVertexArrays(1, &_vaoID);
		glBindVertexArray(_vaoID);

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (char*)NULL + 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (char*)NULL + CUBE_VERTICES_SIZE_BYTES);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
}
