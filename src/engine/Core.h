#include <SDL2/SDL.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <memory>
#include <vector>
#include <iostream>

namespace engine {

	class Entity;
	class Environment;
	class Mouse;
	class Keyboard;

	class Core
	{
		bool running;

		std::weak_ptr<Core> self;
		std::vector<std::shared_ptr<Entity> > entities;
		std::shared_ptr<Entity> currentCameraObject;

		std::shared_ptr<Environment> environment = std::make_shared<Environment>();
		std::shared_ptr<Mouse> mouse = std::make_shared<Mouse>();
		std::shared_ptr<Keyboard> keyboard = std::make_shared<Keyboard>();

		SDL_Window *window;
		ALCdevice* device;
		ALCcontext* context;

	public:

		std::shared_ptr<Environment> getEnvironment() { return environment; }
		std::shared_ptr<Mouse> getMouse() { return mouse; }
		std::shared_ptr<Keyboard> getKeyboard() { return keyboard; }

		static std::shared_ptr<Core> initialize();

		void start();
		void stop() { running = false; }

		void depthPass();
		void renderPass();


		std::shared_ptr<Entity> addEntity();



		template<typename T>
		void getEntities(std::vector<std::shared_ptr<Entity>>& _vector)
		{
			for (std::vector<std::shared_ptr<Entity>>::iterator it = entities.begin(); it != entities.end(); it++)
			{
				bool found = (*it)->checkForComponent<T>();

				if (found)
				{
					_vector.push_back((*it));
				}
			}
		}


	};

}