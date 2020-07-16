namespace engine 
{

	class Environment
	{
		float deltaTime;
		float lastTime;
		float idealTime;

	public:

		float getDeltaTime();

		void initialise();
		void tick();
	};

}