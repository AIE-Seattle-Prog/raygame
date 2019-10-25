#include "game.h"

#include "raylib.h"
#include <iostream>

float wrap(float value, float limit)
{
	return fmodf(fmodf(value, limit) + limit, limit);
}

game::game()
{
	targetFixedStep = 1.0f / 30.0f;
	accumulatedFixedTime = 0.0f;
	physicsScale = 1.0f;
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

		babyPhys.addImpulse({ 0, 50 });
	}
}

void game::tickPhys()
{
	// do physics
	accumulatedFixedTime -= targetFixedStep;

	//std::cout << "PHYS TICK" << std::endl;
	for (auto& i : physObjects)
	{
		i.addAccel(glm::vec2{ 0, 9.8f } * physicsScale);
		i.tickPhys(targetFixedStep);

		i.pos.x = wrap(i.pos.x, (float)GetScreenWidth());
		i.pos.y = wrap(i.pos.y, (float)GetScreenHeight());
	}

	for (auto &i : physObjects)
	{
		for (auto &j : physObjects)
		{
			// skip self collision
			if (&i == &j) { continue; }

			bool collision = false;

			i.collider.match([i, j, &collision](circle c) { if (checkCircleX(i.pos, c, j.pos, j.collider)) { collision = true; } },
              				 [i, j, &collision](aabb a)   { if (checkAABBX(i.pos, a, j.pos, j.collider)) { collision = true; }});

			if (collision) { resolvePhysBodies(i, j); }
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
