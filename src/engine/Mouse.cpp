#include "Mouse.h"

#include <SDL2/SDL.h>
namespace engine
{
	void Mouse::tick()
	{
		SDL_PumpEvents();
		SDL_GetMouseState(&x, &y);
	}

	int Mouse::getMouseX()
	{
		return x;
	}
	int Mouse::getMouseY()
	{
		return y;
	}


}