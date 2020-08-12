#include "Component.h"
#include "Entity.h"
#include "Core.h"

namespace viridian {

	Component::~Component() { }
	void Component::onInit() { }
	void Component::onBegin() { }
	void Component::onTick() { }
	void Component::depthPass() {}
	void Component::renderPass() { }

	std::shared_ptr<Core> Component::getCore()
	{
		return getEntity()->getCore();
	}

	std::shared_ptr<Entity> Component::getEntity()
	{
		return entity.lock();
	}

}