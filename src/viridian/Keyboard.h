#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace viridian
{

	class Keyboard {

		std::vector<int> keysDown;
		std::vector<int> keysUp;


	public:
		void pushKeyDown(int _keyCode);
		void pushKeyUp(int _keyCode);

		void clearKeysStored();

		std::vector<int> getKeysDown() { return keysDown; }
		std::vector<int> getKeysUp() { return keysUp; }
	};

}