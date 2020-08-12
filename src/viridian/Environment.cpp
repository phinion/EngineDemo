#include "Environment.h"
#include <SDL2/SDL.h>

namespace viridian
{
	float Environment::getDeltaTime()
	{
		return deltaTime;
	}

	void Environment::initialise()
	{
		lastTime = SDL_GetTicks();
		idealTime = 1.0f / 60.0f;
	}
	void Environment::tick()
	{
		float time = SDL_GetTicks();
		float difference = time - lastTime;
		deltaTime = difference / 1000;
		lastTime = time;
		if (idealTime > deltaTime)
		{
			SDL_Delay((idealTime - deltaTime) * 1000.0f);
		}
	}
}