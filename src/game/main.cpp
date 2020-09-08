#include <GL/glew.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <viridian/engine.h>

#include <iostream>

int main() 
{
	std::shared_ptr<viridian::Core> engine = viridian::Core::initialize();
	engine->getResources()->addResource<viridian::Shader>(std::string("testShader"), std::string("../resources/shaders/simpleShader.txt"));

	std::shared_ptr<viridian::Entity> firstEntity = engine->addEntity();


	engine->start();

	

	return 0;
}