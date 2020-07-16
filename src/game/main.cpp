#include <GL/glew.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <engine/engine.h>

#include <iostream>

int main() 
{
	std::shared_ptr<engine::Core> core = engine::Core::initialize();

	core->start();

	//std::shared_ptr<engine::Entity> firstEntity = core->addEntity();

	return 0;
}