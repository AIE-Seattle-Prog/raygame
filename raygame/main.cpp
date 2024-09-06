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

#include <cmath>
#include <iostream>

#include "raylib-cpp.hpp"

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int ScreenWidth = 800;
	int ScreenHeight = 450;

	raylib::Window Window(ScreenWidth, ScreenHeight, "raylib-cpp - basic window", FLAG_VSYNC_HINT);
	//Window.SetMonitor(0);
	//Window.ToggleBorderless();

	raylib::Texture DVDLogo("res/aie.png");
	raylib::Color DVDColor = WHITE;

	raylib::Vector2 DVDLocation((int)(Window.GetWidth() / 2), (int)(Window.GetHeight() / 2));
	raylib::Vector2 DVDDirection = { 1, 1 };
	float InitialDVDSpeed = 500.0f;
	float DVDSpeed = InitialDVDSpeed;
	float DVDSpeedGainOnBounce = 10.0f;

	InitAudioDevice();      // Initialize audio device
	raylib::Sound BumpSound("res/pepSound3.wav");
	raylib::Sound CornerSound("res/powerUp2.ogg");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	float DVDValuePeriod = 0.5f;

	// Main game loop
	while (!Window.ShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		DVDLocation += DVDDirection * (DVDSpeed * GetFrameTime());
		DVDLocation = Vector2Clamp(DVDLocation, { 0,0 }, { (float)(Window.GetWidth() - DVDLogo.width), (float)(Window.GetHeight() - DVDLogo.height) });

		bool DidBounce = false;

		if (IsKeyDown('E'))
		{
			DVDSpeed += 500.0f * GetFrameTime();
		}
		if (IsKeyDown('Q'))
		{
			DVDSpeed -= 500.0f * GetFrameTime();
		}

		// right
		int BounceCount = 0;

		if (DVDLocation.x + DVDLogo.width >= Window.GetWidth())
		{
			DVDDirection.x *= -1;
			DVDLocation.x = Window.GetWidth() - DVDLogo.width;
			DidBounce = true;
			++BounceCount;
		}
		// left
		else if (DVDLocation.x <= 0.0f)
		{
			DVDDirection.x *= -1;
			DVDLocation.x = 0;
			DidBounce = true;
			++BounceCount;
		}

		// top
		if (DVDLocation.y <= 0.0f)
		{
			DVDDirection.y *= -1;
			DVDLocation.y = 0;

			DidBounce = true;
			++BounceCount;
		}
		// bottom
		else if (DVDLocation.y + DVDLogo.height >= Window.GetHeight())
		{
			DVDDirection.y *= -1;
			DVDLocation.y = Window.GetHeight() - DVDLogo.height;

			DidBounce = true;
			++BounceCount;
		}

		DVDSpeed += DVDSpeedGainOnBounce * BounceCount;

		// click to control
		if (IsCursorOnScreen() && IsMouseButtonDown(0))
		{
			DVDLocation = GetMousePosition();
			DVDLocation.x -= DVDLogo.GetWidth() / 2;
			DVDLocation.y -= DVDLogo.GetHeight() / 2;
		}

		raylib::Vector3 DVDColorHSV = DVDColor.ToHSV();
		DVDColorHSV.z = 0.15 * std::sinf((2 * 3.14f / DVDValuePeriod) + GetTime()) + 0.65;
		DVDColor = raylib::Color::FromHSV(DVDColorHSV.x, DVDColorHSV.y, DVDColorHSV.z);

		// bounce handling
		if (DidBounce)
		{
			DVDColor = raylib::Color::FromHSV((int)(DVDColorHSV.x + 60) % 360, 1.0f, DVDColorHSV.z);

			if (BounceCount > 1)
			{
				CornerSound.Play();
				DVDSpeed = InitialDVDSpeed;
			}
			else
			{
				//BumpSound.Play();
			}
		}

		// bottom

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		Window.ClearBackground(BLACK);

		DVDLogo.Draw(DVDLocation, DVDColor);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	return 0;
}
