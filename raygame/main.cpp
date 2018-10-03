/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <iostream>
#include <string>

#include "raylib.h"

#include "player.h"
#include "pickup.h"

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);

    std::cout << "Welcome to Move-a-Ball" << std::endl;

    player ball;
    ball.position = { 100, 100 };
    ball.speed = 10.0f;
    ball.score = 0;
    ball.texture = LoadTexture("res\\player.png");

    const int PICKUP_COUNT = 4;
    Texture2D pickupTex = LoadTexture("res\\coin.png");
    pickup pickups[PICKUP_COUNT] =
    {
        {true, 200, 225, 1, pickupTex},
        {true, 400, 225, 1, pickupTex},
        {true, 600, 225, 1, pickupTex},
        {true, 400, 325, 1, pickupTex}
    };

    //--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
        ball.update();
        for (int i = 0; i < PICKUP_COUNT; ++i)
        {
            if (!pickups[i].enabled) { continue; }

            // has the player collided with a pickup?
            if (CheckCollisionRecs(ball.getCollider(), pickups[i].getCollider()))
            {
                pickups[i].enabled = false;
                ball.score++;
            }
        }
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

        ball.draw();
        for (int i = 0; i < PICKUP_COUNT; ++i)
        {
            pickups[i].draw();
        }

        DrawText(std::to_string(ball.score).c_str(), 64, 64, 32, GRAY);
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   

    UnloadTexture(ball.texture);
    UnloadTexture(pickupTex);

	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}