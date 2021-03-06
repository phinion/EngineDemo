#include "Shader.h"
#include "Core.h"
#include "Component.h"
//#include "Transform.h"
#include "Entity.h"
//#include "Camera.h"


namespace viridian {

	Shader::Shader(std::string _filePath) {

		std::string vertexShaderFilePath;
		std::string fragmentShaderFilePath;
		std::string geometryShaderFilePath;

		bool isGeometryShader = false;


		std::ifstream file(_filePath);

		if (!file.is_open())
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		else
		{
			std::string line;
			std::getline(file, line);
			vertexShaderFilePath += line;
			std::getline(file, line);
			fragmentShaderFilePath += line;
			std::getline(file, line);
			geometryShaderFilePath += line;

			//Check if shader program contains geometry shader

			size_t foundGeometryShader = geometryShaderFilePath.find(".geo");
			if (foundGeometryShader != std::string::npos)
			{
				isGeometryShader = true;
			}
		}

		file.close();

		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vertexShaderFile;
		std::ifstream fragmentShaderFile;
		std::ifstream geometryShaderFile;
		// ensure ifstream objects can throw exceptions:
		vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		geometryShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vertexShaderFile.open(vertexShaderFilePath);
			fragmentShaderFile.open(fragmentShaderFilePath);

			if (vertexShaderFile.is_open()) {
				std::cout << "vertex_READ" << std::endl;
			}
			if (fragmentShaderFile.is_open()) {
				std::cout << "fragment_READ" << std::endl;
			}

			//
			std::stringstream vertexShaderStream, fragmentShaderStream;
			vertexShaderStream << vertexShaderFile.rdbuf();
			fragmentShaderStream << fragmentShaderFile.rdbuf();


			// close file handlers
			vertexShaderFile.close();
			fragmentShaderFile.close();
			// convert stream into string
			vertexCode = vertexShaderStream.str();
			fragmentCode = fragmentShaderStream.str();

			// if geometry shader path is present, also load a geometry shader
			if (isGeometryShader)
			{
				geometryShaderFile.open(geometryShaderFilePath);
				std::stringstream geometryShaderStream;
				geometryShaderStream << geometryShaderFile.rdbuf();
				geometryShaderFile.close();
				geometryCode = geometryShaderStream.str();
			}
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vertexShaderSource = vertexCode.c_str();
		const char* fragmentShaderSource = fragmentCode.c_str();

		// Variables to check if compilation for shaders have failed
		int  success;
		char infoLog[512];

		// Vertex Shader
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			std::cin.get();
		}

		// Fragment Shader
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			std::cin.get();
		}

		// Geometry Shader
		unsigned int geometryShader;
		if (isGeometryShader)
		{
			const char * gShaderCode = geometryCode.c_str();
			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometryShader, 1, &gShaderCode, NULL);
			glCompileShader(geometryShader);

			glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
				std::cin.get();
			}
		}

		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		if (isGeometryShader)
		{
			glAttachShader(ID, geometryShader);
		}
		glLinkProgram(ID);
		// print linking errors if any
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		// delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (isGeometryShader)
		{
			glDeleteShader(geometryShader);
		}

	}
	
	void Shader::setViewMatrices()
	{
		std::shared_ptr<Entity> currentCameraEntity = getCore()->getCurrentCameraObject();
		glm::vec3 cameraPos = currentCameraEntity->getComponent<Transform>()->getPos();

		glm::mat4 model = getEntity()->getComponent<Transform>()->getModelMatrix();
		glm::mat4 view = currentCameraEntity->getComponent<Camera>()->getViewMatrix();

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);

		setMat4("model", model);
		setMat4("view", view);
		setMat4("projection", projection);
		setVec3("viewPos", cameraPos);
	}

	void Shader::setViewMatrices(std::shared_ptr<Entity> currentEntity, std::shared_ptr<Entity> currentCameraEntity) 
	{
		glm::mat4 model = currentEntity->getComponent<Transform>()->getModelMatrix();
		glm::mat4 view = currentCameraEntity->getComponent<Camera>()->getViewMatrix();
		glm::vec3 cameraPos = currentCameraEntity->getComponent<Transform>()->getPos();

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);

		setMat4("model", model);
		setMat4("view", view);
		setMat4("projection", projection);
		setVec3("viewPos", cameraPos);
	}
	

	void Shader::use() {
		glUseProgram(ID);
		setViewMatrices();
		setValues();
	}
	void Shader::setBool(const std::string &name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void Shader::setInt(const std::string &name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void Shader::setFloat(const std::string &name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void Shader::setVec2(const std::string &name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void Shader::setVec3(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

}