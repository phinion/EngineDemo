#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H

#include <memory>

namespace engine {

	class Core;
	class Entity;

	class Component
	{
		friend class Entity;

	public:
		virtual ~Component();

	
		std::shared_ptr<Core> getCore();

		std::shared_ptr<Entity> getEntity();

	private:
		std::weak_ptr<Entity> entity;
		bool began;

		virtual void onInit();
		virtual void onBegin();

		virtual void onTick();

		virtual void depthPass();
		virtual void renderPass();
	};

}
#endif
