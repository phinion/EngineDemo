namespace viridian
{
	class Mouse
	{
	public:
		void tick();

		int getMouseX();
		int getMouseY();

	private:
		int x, y;
	};

}