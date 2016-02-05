#include "Shader.h"
#include <SDL\SDL.h>
#include <iostream>
#include <fstream>
#include <vector>

namespace Engine
{
	Shader::Shader() :
		_numAttributes(0),
		_programID(0),
		_vertexShaderID(0), 
		_fragmentShaderID(0)
	{
	}

	Shader::~Shader()
	{
	}

	void Shader::use()
	{
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++) {
			glEnableVertexAttribArray(i);
		}
	}

	void Shader::unuse()
	{
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++) {
			glDisableVertexAttribArray(i);
		}
	}

	void Shader::load()
	{
		if (glIsShader(_vertexShaderID) == GL_TRUE)
			glDeleteShader(_vertexShaderID);

		if (glIsShader(_fragmentShaderID) == GL_TRUE)
			glDeleteShader(_fragmentShaderID);

		if (glIsProgram(_programID) == GL_TRUE)
			glDeleteProgram(_programID);

		compileShaders("Shaders/texture.vert", "Shaders/texture.frag");
		
		addAttribute("v_position");
		addAttribute("v_color");
		addAttribute("v_uv");

		linkShaders();

		std::cout << "Shaders compiled and loaded." << std::endl;
	}

	void Shader::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		//Crée le programme
		_programID = glCreateProgram();

		//Création des shaders
		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexShaderID == 0) { std::cout << "ERROR : Vertex shader failed to be created : "  << SDL_GetError() << std::endl; }

		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0) { std::cout << "ERROR : Fragment shader failed to be created : " << SDL_GetError() << std::endl; }

		compileShader(vertexShaderFilePath, _vertexShaderID);
		compileShader(fragmentShaderFilePath, _fragmentShaderID);
	}

	void Shader::compileShader(const std::string& filePath, GLuint id)
	{
		//Récupération du contenu du fichier vertexShaderFilePath
		std::ifstream vertexFile(filePath);
		if (vertexFile.fail()) { perror(filePath.c_str()); std::cout << "ERROR : Failed to open " + filePath + " : " << SDL_GetError() << std::endl; }

		std::string fileContents = "";
		std::string line;

		while (std::getline(vertexFile, line)) {
			fileContents += line + "\n";
		}

		vertexFile.close();

		//Compilation du vertex shader
		const char* contentsPointer = fileContents.c_str();
		glShaderSource(id, 1, &contentsPointer, nullptr);

		glCompileShader(id);

		//Error checking de la compilation
		GLint isCompiled = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorLog(maxLength + 1);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(id);

			std::printf("%s\n", &(errorLog[0]));
			std::cout << "ERROR : Shader " + filePath + " failed to compile : " << SDL_GetError() << std::endl;
		}
	}

	void Shader::addAttribute(std::string attributeName)
	{
		glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
	}

	void Shader::linkShaders()
	{
		//Attache les shaders au programme
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		//Link le programme
		glLinkProgram(_programID);

		//Error checking du linking
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorLog(maxLength + 1);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

			glDeleteProgram(_programID);
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			std::printf("%s\n", &(errorLog[0]));
			std::cout << "ERROR : Shaders failed to link : " << SDL_GetError() << std::endl;
		}

		//Libération des ressources de shader après compilation
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}

	GLint Shader::getUniformLocation(const std::string &uniformName)
	{
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX) {
			std::cout << "ERROR : Uniform variable " + uniformName + " not found in shader : " << SDL_GetError() << std::endl;
		}
		return location;
	}
}