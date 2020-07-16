#include "Keyboard.h"

namespace engine {

	void Keyboard::pushKeyDown(int _keyCode)
	{
		keysDown.push_back(_keyCode);
	}

	void Keyboard::pushKeyUp(int _keyCode)
	{
		keysUp.push_back(_keyCode);
	}

	void Keyboard::clearKeysStored()
	{
		keysDown.clear();
		keysUp.clear();
	}

}