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

#include "raylib.h"
#include "splashstate.h"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(320, 240, "terryware");
    SetTargetFPS(60);

    gamestate * stateInstance = new splashstate();
    GameStates currentState = SPLASH;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        stateInstance->tick(GetFrameTime());
        GameStates nextState = stateInstance->next();
        if(nextState != currentState)
        {
            delete stateInstance;

            setupGameState(stateInstance, nextState);
            currentState = nextState;
            continue;
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        stateInstance->draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    delete stateInstance;

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}