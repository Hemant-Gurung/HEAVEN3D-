#include "App.h"
#include "InputSystem.h"
int main()
{
	try
	{
		Graphics::create();
		InputSystem::create();
	}
	catch (...) { return -1; }

	{
		try
		{
			App app;
			while (app.isRunning());
		}
		catch (...)
		{
			Graphics::release();
			InputSystem::release();
			return -1;
		}

	}

	Graphics::release();
	InputSystem::release();

	return 0;
}