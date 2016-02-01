#pragma once

#include <string>
#include <GL/glew.h>

namespace Engine
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		void load();
		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void linkShaders();
		void addAttribute(std::string attributeName);
		void use();
		void unuse();
		GLint getUniformLocation(const std::string &uniformName);
		GLuint getProgramID(){ return _programID; }

	private:
		int _numAttributes;
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

		void compileShader(const std::string& filePath, GLuint id);
	};
}