#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <GL/glew.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"
#include "stb_image.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

namespace viridian {

	class Shader;

	class Renderer : public Component {

		unsigned int VAO, VBO;
		std::vector<unsigned int> textures;
		int _noOfVertices = 0;
		std::shared_ptr<Shader> currentShader;
	public:

		void onInit(char const * _path);
		void depthPass();
		void onDisplay();

		void draw();

		void loadTexture(char const * path);
		void addShadow(unsigned int _shadowCubemap);
		void bindTextures();
		void setCurrentShader(std::shared_ptr<Shader> _shader) { currentShader = _shader; }
	};
}

#endif