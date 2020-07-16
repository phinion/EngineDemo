#include "Entity.h"

namespace engine {

	std::shared_ptr<Core> Entity::getCore()
	{
		return core.lock();
	}

	void Entity::onTick()
	{
		for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
			it != components.end(); it++)
		{
			if (!(*it)->began)
			{
				(*it)->onBegin();
				(*it)->began = true;
			}

			(*it)->onTick();
		}
	}

	void  Entity::depthPass()
	{
		for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
			it != components.end(); it++)
		{
			(*it)->depthPass();
		}
	}

	void Entity::renderPass()
	{
		for (std::vector<std::shared_ptr<Component> >::iterator it = components.begin();
			it != components.end(); it++)
		{
			(*it)->renderPass();
		}
	}
}