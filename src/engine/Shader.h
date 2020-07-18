#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Component.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace gibby {

	/**
* stores shader files and passes through variables to shader for use when rendering objects
*/
	class Shader : public Component
	{
		unsigned int ID; ///< shader's id

	public:
		/**
* \brief reads and builds the shader
*/
		void onInit(const GLchar* vertexShaderFilePath, const GLchar* fragmentShaderFilePath, const char* geometryShaderFilePath = nullptr);

		/**
* \brief readys the shader to be used for rendering objects
*/
		void renderPass();

		/**
* \brief set's the model view and projection matrices
*/
		void setViewMatrices();

		/**
* \brief virtual void to be used when shaders need addition variables to be sent through
*/
		virtual void setValues() {}

		/**
* \brief use/activate the shader
*/
		void use();

		// utility uniform functions

		/**
* \brief gets ID
*/
		GLuint getId() { return ID; };
		/**
* \brief sets bool
*/
		void setBool(const std::string &name, bool value) const;
		/**
* \brief sets int
*/
		void setInt(const std::string &name, int value) const;
		/**
* \brief sets float
*/
		void setFloat(const std::string &name, float value) const;
		/**
* \brief sets vec2
*/
		void setVec2(const std::string &name, const glm::vec2 &value) const;
		/**
* \brief sets vec2
*/
		void setVec2(const std::string &name, float x, float y) const;
		/**
* \brief sets vec3
*/
		void setVec3(const std::string &name, const glm::vec3 &value) const;
		/**
* \brief sets vec3
*/
		void setVec3(const std::string &name, float x, float y, float z) const;
		/**
* \brief sets vec4
*/
		void setVec4(const std::string &name, const glm::vec4 &value) const;
		/**
* \brief sets vec4
*/
		void setVec4(const std::string &name, float x, float y, float z, float w);
		/**
* \brief sets mat2
*/
		void setMat2(const std::string &name, const glm::mat2 &mat) const;
		/**
* \brief sets mat3
*/
		void setMat3(const std::string &name, const glm::mat3 &mat) const;
		/**
* \brief sets mat4
*/
		void setMat4(const std::string &name, const glm::mat4 &mat) const;
	};

}