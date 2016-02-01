#include "picoPNG.h"
#include "Texture.h"
#include <iostream>
#include <fstream>

namespace Engine
{
	Texture Texture::loadPNG(std::string filePath)
	{
		Texture texture = {};
		std::vector<unsigned char> in;
		std::vector<unsigned char> out;
		unsigned long width, height;

		//Mise en buffer du fichier et error checking
		if (Texture::readFileToBuffer(filePath, in) == false)
		{
			std::cout << "Failed to load PNG file " << filePath << " to buffer." << std::endl;
		}

		//Decoding du fichier PNG
		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
		//Error checking
		if (errorCode != 0)
		{
			std::cout << "decodePNG failed with error : " << errorCode << std::endl;
		}

		//Définition des proportions de la texture
		texture.width = width;
		texture.height = height;

		//Génération de la texture
		glGenTextures(1, &(texture.id));

		//Binding de la texture
		glBindTexture(GL_TEXTURE_2D, texture.id);

		//Application du PNG sur la texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		//Ajout de quelques paramètres (mosaïque, interpolation, etc)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//Mipmapping (blur des pixels en résolutions faibles)
		glGenerateMipmap(GL_TEXTURE_2D);

		//Unbinding de la texture
		glBindTexture(GL_TEXTURE_2D, 0);

		return texture;
	}

	bool Texture::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}

		//Récupération de la taille du fichier
		file.seekg(0, std::ios::end); // on met le curseur à la toute fin du fichier pour compter les nombre de bytes parcourus
		int fileSize = file.tellg(); // on récupère ce nombre
		file.seekg(0, std::ios::beg); // on remet le curseur au début pour pouvoir le lire
		fileSize -= file.tellg(); //On enlève les headers du fichier

		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);
		file.close();

		return true;
	}
}