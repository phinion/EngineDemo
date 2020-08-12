#include "engine.h"

#include <GL/glew.h>
#include <iostream>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

namespace viridian {

	// Creates window
	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> core = std::make_shared<Core>();
		core->running = false;
		core->self = core;

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::exception();
		}

		core->window = SDL_CreateWindow("Yash Vishwanath - Engine Demo",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			1280, 720,
			SDL_WINDOW_OPENGL | SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_GRABBED);

		//SDL_SetRelativeMouseMode(SDL_TRUE);

		core->environment->initialise();

		if (!SDL_GL_CreateContext(core->window))
		{
			throw std::exception();
		}

		if (glewInit() != GLEW_OK)
		{
			throw std::exception();
		}

		core->device = alcOpenDevice(NULL);
		if (!core->device)
		{
			throw std::exception();
		}

		core->context = alcCreateContext(core->device, NULL);
		if (!core->context)
		{
			alcCloseDevice(core->device);
			throw std::exception();
		}
		if (!alcMakeContextCurrent(core->context))
		{
			alcDestroyContext(core->context);
			alcCloseDevice(core->device);
			throw std::exception();
		}

		SDL_ShowCursor(SDL_DISABLE);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		return core;
	}

	void Core::start()
	{

		running = true;
		while (running)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				switch (event.type) {
				case SDL_KEYDOWN:
					keyboard->pushKeyDown(event.key.keysym.sym);
					break;
				case SDL_KEYUP:
					keyboard->pushKeyUp(event.key.keysym.sym);
					break;
				}

				if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
				{
					running = false;
				}
			}

			for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
				it != entities.end(); it++)
			{
				(*it)->onTick();
			}

			mouse->tick();
			environment->tick();
			keyboard->clearKeysStored();

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glViewport(0, 0, 1280, 720);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			renderPass();

			SDL_GL_SwapWindow(window);
		}
	}

	void Core::depthPass()
	{
	}

	void Core::renderPass()
	{
		for (std::vector<std::shared_ptr<Entity> >::iterator it = entities.begin();
			it != entities.end(); it++)
		{
			(*it)->renderPass();
		}
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		entities.push_back(rtn);
		rtn->self = rtn;
		rtn->core = self;

		return rtn;
	}
}