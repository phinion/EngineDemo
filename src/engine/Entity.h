#include "Component.h"

#include <memory>
#include <vector>

#define ADDCOMPONENT \
  std::shared_ptr<T> rtn = std::make_shared<T>(); \
  rtn->entity = self; \
  rtn->began = false; \
  components.push_back(rtn);

namespace engine {

	class Core;

	class Entity
	{
		friend class Core;

	public:
		
		template <typename T>
		std::shared_ptr<T> getComponent()
		{
			for (size_t i = 0; i < components.size(); i++)
			{
				std::shared_ptr<T> tst = std::dynamic_pointer_cast<T>(components.at(i));

				if (tst)
				{
					return tst;
				}
			}

			throw std::exception();
		}

		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			ADDCOMPONENT
				rtn->onInit();

			return rtn;
		}

		template <typename T, typename A>
		std::shared_ptr<T> addComponent(A a)
		{
			ADDCOMPONENT
				rtn->onInit(a);

			return rtn;
		}

		template <typename T, typename A, typename B>
		std::shared_ptr<T> addComponent(A a, B b)
		{
			ADDCOMPONENT
				rtn->onInit(a, b);

			return rtn;
		}

		template <typename T, typename A, typename B, typename C>
		std::shared_ptr<T> addComponent(A a, B b, C c)
		{
			ADDCOMPONENT
				rtn->onInit(a, b, c);

			return rtn;
		}

		template<typename T>
		bool checkForComponent()
		{
			for (std::vector<std::shared_ptr<Component>>::iterator it = components.begin(); it != components.end(); it++)
			{
				std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(*it);

				if (rtn)
				{
					return true;
				}
			}

			return false;
		}

		std::shared_ptr<Core> getCore();

	private:
		std::weak_ptr<Entity> self;
		std::weak_ptr<Core> core;
		std::vector<std::shared_ptr<Component> > components;

		void onTick();
		void depthPass();
		void renderPass();

	};

}