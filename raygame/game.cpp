#include "game.h"

#include "raylib.h"
#include <iostream>

game::game()
{
	targetFixedStep = 1.0f / 30.0f;
	accumulatedFixedTime = 0.0f;
}

void game::init()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------
}

void game::tick()
{
	// do update
	accumulatedFixedTime += GetFrameTime();

	bool mb0 = IsMouseButtonPressed(0);
	bool mb1 = IsMouseButtonPressed(1);

	if (mb0 || mb1)
	{
		physObjects.emplace_back();
		std::cout << "Added a physics object!" << std::endl;

		auto& babyPhys = physObjects[physObjects.size() - 1];
		auto mousePos = GetMousePosition();
		babyPhys.pos = { mousePos.x, mousePos.y };
		
		if (mb0)
		{
			babyPhys.collider = circle{ 15.0f };
		}
		else
		{
			babyPhys.collider = aabb{ {15, 15} };
		}
	}
}

void game::tickPhys()
{
	// do physics
	accumulatedFixedTime -= targetFixedStep;

	//std::cout << "PHYS TICK" << std::endl;
	for (auto& i : physObjects)
	{
		i.tickPhys(targetFixedStep);
	}

	for (auto &i : physObjects)
	{
		for (auto &j : physObjects)
		{
			// skip self collision
			if (&i == &j) { continue; }

			i.collider.match([i, j](circle c) { if (checkCircleX(i.pos, c, j.pos, j.collider)) { std::cout << "collision!" << std::endl; } },
              				 [i, j](aabb a) { if (checkAABBX(i.pos, a, j.pos, j.collider)) { std::cout << "colllllllision." << std::endl; }});
		}
	}
}

void game::draw() const
{
	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();

	ClearBackground(RAYWHITE);

	for (const auto& i : physObjects)
	{
		i.draw();
	}

	EndDrawing();
	//----------------------------------------------------------------------------------
}

void game::exit()
{
	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

}

bool game::shouldClose() const
{
	return WindowShouldClose();
}

bool game::shouldPhysics() const
{
	return accumulatedFixedTime >= targetFixedStep;
}
