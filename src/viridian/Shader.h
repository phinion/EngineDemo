#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Resource.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace viridian {
	
	class Shader: public Resource
	{
		unsigned int ID; ///< shader's id

	public:
	
		Shader(std::string _filePath);
		void onInit(const GLchar* vertexShaderFilePath, const GLchar* fragmentShaderFilePath, const char* geometryShaderFilePath = nullptr);

		//void renderPass();

		void use();
		void setViewMatrices();
		void setViewMatrices(std::shared_ptr<Entity> currentEntity, std::shared_ptr<Entity> currentCameraEntity);
		virtual void setValues() {}
		

		// utility uniform functions
		GLuint getId() { return ID; };	
		void setBool(const std::string &name, bool value) const;		
		void setInt(const std::string &name, int value) const;		
		void setFloat(const std::string &name, float value) const;	
		void setVec2(const std::string &name, const glm::vec2 &value) const;		
		void setVec2(const std::string &name, float x, float y) const;		
		void setVec3(const std::string &name, const glm::vec3 &value) const;		
		void setVec3(const std::string &name, float x, float y, float z) const;	
		void setVec4(const std::string &name, const glm::vec4 &value) const;		
		void setVec4(const std::string &name, float x, float y, float z, float w);		
		void setMat2(const std::string &name, const glm::mat2 &mat) const;	
		void setMat3(const std::string &name, const glm::mat3 &mat) const;		
		void setMat4(const std::string &name, const glm::mat4 &mat) const;
	};

}