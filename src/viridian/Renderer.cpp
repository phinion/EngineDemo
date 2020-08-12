#include "Renderer.h"

namespace viridian {

	//onInit();
	void Renderer::onInit(char const * _path)
	{
		std::string line;
		std::ifstream infile(_path);

		if (infile.is_open()) {

			//Get number of values per line
			std::getline(infile, line, ',');
			int _size = std::stoi(line);
			std::cout << "size of line " << _size << std::endl;

			//Get number of buffers per line
			std::getline(infile, line, ',');
			int _noOfBuffers = std::stoi(line);
			std::cout << "number of buffers per line " << _noOfBuffers << std::endl;

			//gets size of each buffer
			std::vector<int> _sizeOfIndividualBuffer;
			for (int a = 0; a < _noOfBuffers; a++) {
				std::getline(infile, line, ',');
				_sizeOfIndividualBuffer.push_back(std::stoi(line));
				std::cout << "size of individual buffers " << _sizeOfIndividualBuffer[a] << std::endl;
			}

			//gets number of verties
			std::getline(infile, line, ',');
			_noOfVertices = std::stoi(line);
			std::cout << "number of vertices " << _noOfVertices << std::endl;

			std::vector<float> vertices;
			int vertexCount = 0;

			//  Read the file    
			while (std::getline(infile, line, ','))
			{
				vertexCount++;
				vertices.push_back(std::stof(line));
			}
			infile.close();
			std::cout << vertexCount << std::endl;


			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices.at(0)), &vertices.at(0), GL_STATIC_DRAW);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(&vertices.at(0)) * vertices.size(), &vertices, GL_STATIC_DRAW);

			int _offset = 0;
			for (int a = 0; a < _noOfBuffers; a++)
			{
				glVertexAttribPointer(a, _sizeOfIndividualBuffer[a], GL_FLOAT, GL_FALSE, _size * sizeof(float), (void*)(_offset * sizeof(float)));
				glEnableVertexAttribArray(a);
				_offset += _sizeOfIndividualBuffer[a];
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		else
		{
			std::cout << "File data not read!!" << std::endl;
		}
	}

	void Renderer::loadTexture(char const * path)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			textures.push_back(textureID);
			std::cout << "Texture loaded at path: " << path << std::endl;

		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
		}

		stbi_image_free(data);
	}

	void Renderer::addShadow(unsigned int _shadowCubemap)
	{
		textures.push_back(_shadowCubemap);
	}

	void Renderer::bindTextures()
	{

		for (int a = 0; a < textures.size(); a++)
		{
			glActiveTexture(GL_TEXTURE0 + a);
			glBindTexture(GL_TEXTURE_2D, textures[0]);
		}

		/*if (textures.size() > 1) {
			glActiveTexture(GL_TEXTURE0 + textures.size() - 1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textures[textures.size() - 1]);
		}*/

	}
	void Renderer::depthPass()
	{
		draw();
	}

	void Renderer::onDisplay()
	{
		bindTextures();
		draw();
	}

	void Renderer::draw()
	{

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, _noOfVertices);

		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}

}