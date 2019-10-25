#include "raylib.h"

#include "game.h"

int main()
{
	game app;
	app.init();
	app.targetFixedStep = 1.0f / 30.0f; // target physics tick rate

	while (!app.shouldClose())
	{
		app.tick();

		while (app.shouldPhysics())
		{
			app.tickPhys();
		}

		app.draw();
	}

	app.exit();

	return 0;
}